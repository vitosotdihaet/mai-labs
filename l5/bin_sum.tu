tape:
  11010 101
prog:
0, ,<,nd

//CLONE
nd,1,<,nd
nd,0,<,nd
nd, ,<,2nd

2nd,1,<,2nd
2nd,0,<,2nd
2nd, ,>,copy

copy,1, ,m1
copy,0, ,m0
copy, ,>,check

check,1,=,copy
check,0,=,copy
check, ,=,copy2

copy2,1, ,m11
copy2,0, ,m00
copy2, ,>,copy2

m1, ,<,s1
m11, ,<,s11
s1, ,1,cl1
s11, ,1,cl11

m0, ,<,s0
m00, ,<,s00
s0, ,0,cl0
s00, ,0,cl00

//ONE1!!!
cl1,1,>,cl1
cl1,0,>,cl1
cl1, ,>,cl1n

cl1n,1,>,cl1n
cl1n,0,>,cl1n
cl1n, ,>,cl1w

cl1w,1,>,cl1w
cl1w,0,>,cl1w
cl1w, ,>,set1

//ONE2!!!
cl11,1,>,cl11
cl11,0,>,cl11
cl11, ,>,cl11n

cl11n,1,>,cl11n
cl11n,0,>,cl11n
cl11n, ,>,cl11w

cl11w,1,>,cl11w
cl11w,0,>,cl11w
cl11w, ,>,set11

//SET_ONES
set1,1,>,set1
set1,0,>,set1
set1, ,1,tcpf

set11,1,>,set11
set11,0,>,set11
set11, ,1,t

//ZERO1!!!
cl0,1,>,cl0
cl0,0,>,cl0
cl0, ,>,cl0n

cl0n,1,>,cl0n
cl0n,0,>,cl0n
cl0n, ,>,cl0w

cl0w,1,>,cl0w
cl0w,0,>,cl0w
cl0w, ,>,set0

//ZERO2!!!
cl00,1,>,cl00
cl00,0,>,cl00
cl00, ,>,cl00n

cl00n,1,>,cl00n
cl00n,0,>,cl00n
cl00n, ,>,cl00w

cl00w,1,>,cl00w
cl00w,0,>,cl00w
cl00w, ,>,set00


//SET_ZEROES
set0,1,>,set0
set0,0,>,set0
set0, ,0,tcpf

set00,1,>,set00
set00,0,>,set00
set00, ,0,t

//BACK!!!
tcpf,1,<,tcpf
tcpf,0,<,tcpf
tcpf, ,<,tcpfn

tcpfn,1,<,tcpfn
tcpfn,0,<,tcpfn
tcpfn, ,<,tcpfnw

tcpfnw,1,<,tcpfnw
tcpfnw,0,<,tcpfnw
tcpfnw, ,=,copy

t,1,<,t
t,0,<,t
t, ,<,tn

tn,1,<,tn
tn,0,<,tn
tn, ,=,c

c, ,<,c1
c1,1,<,tw
c1,0,<,tw
c1, , ,nl

tw,1,<,tw
tw,0,<,tw
tw, ,=,copy2

//NORMALIZE
//NORMALIZE FIRST
nl, ,<,nm

nls,1,<,nm
nls,0,<,nm
nls, ,<,nc

nc, ,<,nm

nm,1, ,nm1
nm,0, ,nm0
nm, ,<,ncc

nm1, ,>,ns1
ns1, ,1,nls

nm0, ,>,ns0
ns0, ,0,nls

ncc,1,=,nm
ncc,0,=,nm
ncc, ,<,nlff

nlf,1,=,nm
nlf,0,=,nm
nlf, ,<,nlss

//NORMALIZE SECOND
nlss,1,<,nmm
nlss,0,<,nmm
nlss, ,<,nccc

nccc, ,<,nmm

nmm1, ,>,nss1
nss1, ,1,nlss

nmm0, ,>,nss0
nss0, ,0,nlss

nmm,1, ,nmm1
nmm,0, ,nmm0
nmm, ,<,ncccc

ncccc,1,=,nmm
ncccc,0,=,nmm
ncccc, ,=,skip1

nlff,1,=,nmm
nlff,0,=,nmm

//SNAP BACK
skip1,1,>,skip2
skip1,0,>,skip2
skip1, ,>,skip2

skip2,1,>,skip2
skip2,0,>,skip2
skip2, ,>,check_skip

check_skip,1,=,skip2
check_skip,0,=,skip2
check_skip, ,<,sum

//SUM
sum, ,<,sf

sf,|, ,b
sf,1,|,mv1
sf,0,|,mv0
sf, ,=,delo

mv1,|,<,mv1n

mv1n,1,<,mv1n
mv1n,0,<,mv1n
mv1n, ,<,e1

e1,-, ,ed1
ed1, ,<,e1
e1,1,-,opo
e1,0,-,opz
e1, ,<,e1

mv0,|,<,mv0n

mv0n,1,<,mv0n
mv0n,0,<,mv0n
mv0n, ,<,e0

e0,-, ,ed0
ed0, ,<,e0
e0,1,-,opz
e0,0,-,zpz
e0, ,<,e0

opo,-,>,opo
opo, ,>,p2

opz,-,>,opz
opz, ,>,p1

zpz,-,>,zpz
zpz, ,>,p0

p2,1,>,p2
p2,0,>,p2
p2, ,>,p2
p2,|,=,ce2

ce2,|,<,ce2
ce2,1,>,p22
ce2,0,>,p22
ce2, ,>,l2

p22,|,>,p22
p22, ,>,p2!
p2!, ,2,b

l2,|,>,p22

p1,1,>,p1
p1,0,>,p1
p1, ,>,p1
p1,|,=,ce1

ce1,|,<,ce1
ce1,1,>,p11
ce1,0,>,p11
ce1, ,>,l1

p11,|,>,p11
p11, ,>,p1!
p1!, ,1,b

l1,|,>,p11

p0,1,>,p0
p0,0,>,p0
p0, ,>,p0
p0,|,=,ce0

ce0,|,<,ce0
ce0,1,>,p00
ce0,0,>,p00
ce0, ,>,l0

p00,|,>,p00
p00, ,>,p0!
p0!, ,0,b

l0,|,>,p00

b,2,<,b
b,1,<,b
b,0,<,b
b, ,<,sf

//ADD!!!
delo, ,<,delo
delo,-,=,cba

cba,-,<,cba
cba,1,>,adde
cba,0,>,adde
cba, ,>,zero
zero,-,0,adde

adde,1,-,pk1
adde,0,-,pk0
adde, ,<,adde
adde,-,=,checkl

pk1,-,>,k1
k1, , ,dob1
k1,-, ,dob1

pk0,-,>,k0
k0, , ,dob0
k0,-, ,dob0

dob1,2,<,dob1!
dob1,1,<,dob1!
dob1,0,<,dob1!
dob1, ,>,dob1
dob1,-,>,dob1
dob1!, ,1,1b

dob0,2,<,dob0!
dob0,1,<,dob0!
dob0,0,<,dob0!
dob0, ,>,dob0
dob0,-,>,dob0
dob0!, ,0,1b

1b,1,<,adde
1b,0,<,adde

checkl,-,<,checkl
checkl,1,=,adde
checkl,0,=,adde
checkl, ,>,delete

delete,-, ,kras

//KRASIVO!!!
kras,2,>,number
kras,1,>,number
kras,0,>,number
kras, ,>,kras

number,2,=,two
number,1,>,number
number,0,>,number
number,+,0,hmm
hmm,0,>,number
number, , ,number

two,2,+,left
left,+,<,left
left,1,2,two
left,0,1,number
left, ,1,number
