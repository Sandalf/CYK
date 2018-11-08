# CYK
CYK algorithm written in C++ for the automatons class

# Grammar in CNF
S -> x | ClD1

R -> r | CcD1

Cc -> c

D1 -> SR

C1 -> l

# Test Data
Here are some string accepted or rejected by the grammar

| Accepted        | Not Accepted |
|-----------------|--------------|
| x               | lxl          |
| lxr             | xx           |
| llxr            | rlx          |
| lxcx            | xllx         |
| llxrr           | lllxxxrrr    |
| lllxrcllxrrrcxr | rrlxl        |
| lxcxr           | lxrr         |
| lxcxcxr         | lxrlxr       |
| llllxcxrrrr     | lllxcrrr     |