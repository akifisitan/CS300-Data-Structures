# Skyline 

    input:
    4
    2 50 10
    35 20 55
    30 60 45
    5 75 25

    order:
    (0) 02 05 10 25 30 35 45 55
    (0) 50 75 50 75 60 20 60 20
    use sorting algorithm and remove duplicates?
    check values of 0 and 2 whichever is bigger makes skyline
    output:
    0 0
    2 50
    5 75
    25 0
    30 60
    45 20
    55 0

    location = [NULL | 3, 1, 2, 4]

    heap = [NULL | itemX, itemY, itemZ, itemP]

    on insert 1 -> heap [NULL | ]


    itemX.label = 2
    itemY.label = 3
    itemZ.label = 1
    itemP.label = 4


    find heap location with label 1?
    check location[1] -> 3

    find heap location with label 2?
    check location[2] -> 1

    find heap location with label 3?
    check location[3] -> 2
    check heap[location[3]] then.


    find heap location with label 4?
    check location[4] -> 4
    check heap[4] then.

    after insertion what if heap[4] changes?
    mimic the change in location
    location[1] = 3 -> heap[3]
    location[2] = 1 -> heap[1]
    location[3] = 2 -> heap[2]
    location[4] = 4 -> heap[4]
