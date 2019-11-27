# update_ttree
Because you'd be surprised how not straightforward this is...

## Create an input TTree

Compile `make_tree.cpp`,
```bash
g++ -o run make_tree.cpp `root-config --cflags --libs`
./run
```
and execute,
```bash
./run
```
to produce a ROOT file containing a TTree "mytree" with three variables:
```
└─ $ root tree.root
   ------------------------------------------------------------
  | Welcome to ROOT 6.12/06                http://root.cern.ch |
  |                               (c) 1995-2017, The ROOT Team |
  | Built for macosx64                                         |
  | From tag v6-12-06, 9 February 2018                         |
  | Try '.help', '.demo', '.license', '.credits', '.quit'/'.q' |
   ------------------------------------------------------------

root [0]
Attaching file tree.root as _file0...
(TFile *) 0x7fb19c234c30
root [1] .ls
TFile**         tree.root
 TFile*         tree.root
  KEY: TTree    mytree;1        mytree
root [2] mytree->Print()
******************************************************************************
*Tree    :mytree    : mytree                                                 *
*Entries :     1000 : Total =           14017 bytes  File  Size =        867 *
*        :          : Tree compression factor =  31.25                       *
******************************************************************************
*Br    0 :var0      : var0/F                                                 *
*Entries :     1000 : Total  Size=       4554 bytes  File Size  =        130 *
*Baskets :        1 : Basket Size=      32000 bytes  Compression=  31.33     *
*............................................................................*
*Br    1 :var1      : var1/F                                                 *
*Entries :     1000 : Total  Size=       4554 bytes  File Size  =        130 *
*Baskets :        1 : Basket Size=      32000 bytes  Compression=  31.33     *
*............................................................................*
*Br    2 :var2      : var2/F                                                 *
*Entries :     1000 : Total  Size=       4554 bytes  File Size  =        131 *
*Baskets :        1 : Basket Size=      32000 bytes  Compression=  31.09     *
*............................................................................*
```

The variables have the same value for each event: `var0 = 2`, `var1 = 2`, and `varN = 49`.

## Add a new Branch to an existing TTree (without making a new output ROOT file)

Compile the code,
```bash
g++ -o update_tree update_tree.cpp `root-config --cflags --libs`
```
and execute in the directory containing the output ROOT file from before,
```bash
./update_tree
```
Now look inside of the file `tree.root`:

```
└─ $ root tree.root
   ------------------------------------------------------------
  | Welcome to ROOT 6.12/06                http://root.cern.ch |
  |                               (c) 1995-2017, The ROOT Team |
  | Built for macosx64                                         |
  | From tag v6-12-06, 9 February 2018                         |
  | Try '.help', '.demo', '.license', '.credits', '.quit'/'.q' |
   ------------------------------------------------------------

root [0]
Attaching file tree.root as _file0...
(TFile *) 0x7f8066a24550
root [1] .ls
TFile**         tree.root
 TFile*         tree.root
  KEY: TTree    mytree;2        mytree
root [2] mytree->Print()
******************************************************************************
*Tree    :mytree    : mytree                                                 *
*Entries :     1000 : Total =           18665 bytes  File  Size =       1044 *
*        :          : Tree compression factor =  31.25                       *
******************************************************************************
*Br    0 :var0      : var0/F                                                 *
*Entries :     1000 : Total  Size=       4554 bytes  File Size  =        130 *
*Baskets :        1 : Basket Size=      32000 bytes  Compression=  31.33     *
*............................................................................*
*Br    1 :var1      : var1/F                                                 *
*Entries :     1000 : Total  Size=       4554 bytes  File Size  =        130 *
*Baskets :        1 : Basket Size=      32000 bytes  Compression=  31.33     *
*............................................................................*
*Br    2 :var2      : var2/F                                                 *
*Entries :     1000 : Total  Size=       4554 bytes  File Size  =        131 *
*Baskets :        1 : Basket Size=      32000 bytes  Compression=  31.09     *
*............................................................................*
*Br    3 :varN      : varN/F                                                 *
*Entries :     1000 : Total  Size=       4643 bytes  One basket in memory    *
*Baskets :        0 : Basket Size=      32000 bytes  Compression=   1.00     *
*............................................................................*
```
You see a new variable `varN` which, if you look inside of `update_tree.cpp`, is simply `var0 + var1`. If you look at the value of `varN` you should get 4 on each event. If not, then you have more Orwellian concerns to worry about...

