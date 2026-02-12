# NanoTekSpice Architecture

there are frameworks inside frameworks

## The files we read from:

input and outputs are the most basic ones.

They only have a single wire thats why its in:1

the input can only be connected to a single thing. Same thing for the output.

```
# Basic wire, direct link input to output.
#
# INPUT ---> OUTPUT

.chipsets:
input in
output out

.links:
in:1 out:1
```

but this is not all. there are also some very simple one that serve the same purpose

```
# Basic wire, direct link true to output.
#
# TRUE ---> OUTPUT

.chipsets:
true in
output out

.links:
in:1 out:1
```

however this is not all as we can also have some very complex frameworks with multiple input and outputs that have to be connected. the name does not matter, but the type (which will most likely be a class) does matter

```
# OR logic gates (4071)
#
#           +---------4071---------+
# in_01  -1-|>-+---\       ignored-|-14-
#           |  | or |-+            |
# in_02  -2-|>-+---/  |     /---+-<|-13- in_13
#           |         |  +-| or |  |
# out_03 -3-|<--------+  |  \---+-<|-12- in_12
#           |            |         |
# out_04 -4-|<--------+  +-------->|-11- out_11
#           |         |            |
# in_05  -5-|>-+---\  |  +-------->|-10- out_10
#           |  | or |-+  |         |
# in_06  -6-|>-+---/     |  /---+-<|-9-  in_09
#           |            +-| or |  |
#        -7-|-ignored       \---+-<|-8-  in_08
#           +----------------------+

.chipsets:
input in_01
input in_02
output out_03
output out_04
input in_05
input in_06
input in_08
input in_09
output out_10
output out_11
input in_12
input in_13
4071 gate

.links:
in_01:1 gate:1
in_02:1 gate:2
out_03:1 gate:3
out_04:1 gate:4
in_05:1 gate:5
in_06:1 gate:6
in_08:1 gate:8
in_09:1 gate:9
out_10:1 gate:10
out_11:1 gate:11
in_12:1 gate:12
in_13:1 gate:13
```

## The user commands:

there are 5 possible commands

- exit : exits the program
- display : prints the current tick and the value of all inputs and outputs the standard output, each sorted by name in ASCII order.
- input=value : changes the value of an input. Possible value are 0, 1 and U. This also apply to clocks.
- simulate : simulate a tick of the circuit.
- loop : continuously runs the simulation (simulate, display, simulate, ...) without displaying a prompt, until SIGINT (CTRL+C) is received.

example:

```
~/B-OOP-400> cat -e or_gate.nts
.chipsets:
input   a$
input   b$
4071    or$
output  s$
.links:$
a:1     or:1$
b:1     or:2$
or:3    s:1$
~/B-OOP-400> ./nanotekspice or_gate.nts
> *b=0*
> *a=1*
> *simulate*
> *display*
tick: 1
input(s):
  a: 1
  b: 0
output(s):
  s: 1
> *exit*
~/B-OOP-400> echo $?
0
```

## Architecture decisions: (this is all up to debate, there are the rumblings of an insane man)

since this is essentially a big graph, we shall use tree where nodes are connected to each other througfh pointers or smth similar. Every component should be a class.

On initialisation, all of them go in a big array (a map), as Icomponents?

this is done so that we can keep track of them both to delete them if necessary, but also that the user can initialse them in the cli when needed.

Everything should reside in a big class called Circuit. it should be able to add components to the map, get components, and call the simulate in the right order.

when we come across the links, we start connecting them. (theoretically tnis is done through a big parent class theat every body inherits from called Acomponent) 

The logic of every class should be self contained.

What does this mean:

- Every class only cares about itself, and the only thing it checks otherwise is if its connections are initialised correctly. example of andcomponent below alongside its parent class
- question: should input and outputs be separate classes? ye right?
- question: how does simulate actually work? how does the order of execution work exactly? does every class need its own simulate?

### Example of a component

```cpp
class AComponent : public virtual IComponent
{
    private:
    protected:
        struct Link { //were gunna make a list of which links are connected where
            nts::IComponent *component = nullptr; //which component are we talking about
            std::size_t pin = 0; //other pin
        };

        //index of map is gonna be our pin, and holds other pin as well as ref to other component
        std::map<std::size_t, Link> _links; //just make a map of links

    public:
        AComponent() = default;
        //AComponent(const AComponent& other);
        //AComponent& operator=(const AComponent& other);
        ~AComponent() = default;

        //void display(std::ostream& os = std::cout);
        void simulate(std::size_t tick) override
        {
            return;
        }

        //set da link
        void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override
        {
            _links[pin] = {&other, otherPin};
        }

        nts::Tristate getLink(std::size_t pin)
        {
            if (_links.count(pin) == 0)
                return Undefined;
            return _links[pin].component->compute(_links[pin].pin); //compute takes as an input the supposed return pin
        }
};

class AndComponent : public virtual AComponent
{
    private:
    protected:
    public:

        nts :: Tristate compute ( std :: size_t pin ) override
        {
            if (pin != 3) //the return pin
                return Undefined;
            auto a = getLink(1);
            auto b = getLink(2);

            //most scuffed way of doing and statement, but can't think of anything better
            if (a == Undefined || b == Undefined)
                return Undefined;
            if (a == False || b == False)
                return False;
            return True;
        }

};
```