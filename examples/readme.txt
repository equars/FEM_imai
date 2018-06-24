Readme of this example.

this is one of a example that solve stress or strain distribution with the fem program made by imai.
the example problem is that...

       2 ___________________________________ 4 ___________________________________ 6 ___________________________________ 8 ----> 10MN
       |\                                    |\                                    |\                                    |
       |   \                                 |   \                                 |   \                                 |
       |     \                               |     \                               |     \                               |
       |       \                             |       \                             |       \                             |
       |          \               B          |          \               D          |          \               F          |
       |            \                        |            \                        |            \                        |
       |               \                     |               \                     |               \                     |
       |                 \                   |                 \                   |                 \                   |
       |                   \                 |                   \                 |                   \                 |
       |                      \              |                      \              |                      \              |
       |            A           \            |            C           \            |            E           \            |
       |                           \         |                           \         |                           \         |
y      |                             \       |                             \       |                             \       |
^      |                               \     |                               \     |                               \     |
|      |                                  \  |                                  \  |                                  \  |
|      1 ----------------------------------- 3 ----------------------------------- 5 ----------------------------------- 7 ----> 10MN
|
L----------> x

1:(0, 0) , 2:(1.0, 0) , 3:(0, 1.0) , 4:(1.0, 1.0)...

Node 1 and 2 are fixed to all directions, and model will be added x axis load by node 7 and 8.

Width : 3m
Height : 1m
Thickness : 1m
