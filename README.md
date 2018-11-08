# CYK
CYK algorithm written in C++ for the automatons class

# Grammar in CNF
S -> x | ClD1

R -> r | CcD1

Cc -> c

D1 -> SR

Cl -> l

# Test Data
Here are some strings accepted and rejected by the grammar.

| Accepted        | Rejected     |
|-----------------|--------------|
| x               | lxl          |
| lxr             | xx           |
| lxcllxrrr       | rlx          |
| lxcxclxrr       | xllx         |
| llxrr           | lllxxxrrr    |
| lllxrcllxrrrcxr | rrlxl        |
| lxcxr           | lxrr         |
| lxcxcxr         | lxrlxr       |
| llllxcxrrrr     | lllxcrrr     |