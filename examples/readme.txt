Readme of this example.

this is one of a example that solve stress or strain distribution with the fem program made by imai.
the example problem is that...

       3 ___________________________________ 4
       |\                                    |
       |   \                                 |
       |     \                               |
       |       \                             |
       |          \               B          |
       |            \                        |
       |               \                     |
       |                 \                   |
       |                   \                 |
       |                      \              |
       |            A           \            |
       |                           \         |
y      |                             \       |
^      |                               \     |
|      |                                  \  |
|      1 ----------------------------------- 2
|
L----------> x

1:(0,0) , 2:(1.0,0) , 3:(0,1.0) , 4:(1.0,1.0)

Node 1 and 3 are fixed to all directions, and model will be added x axis strain by node 2 and 4. 
