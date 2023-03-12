# Point Quadtree
- Each node contains 7 values: NW, NE, SW, SE, XCOORD, YCOORD, NAME
## Operations
- Insert
- Find

## Inputs
### cities.txt
	2D space and cities located in this space
	1. <x> <y> represent the upper right where as the lower left is 0,0
	next lines: <city_name> <x> <y>
	city names are single and coordinates are not negative 
### queries.txt
	queries to be answered
	<x> <y> <radius>  
	1. comma separated list of cities within radius distance from x,y
	2. comma separated list of cities visited during the search operation

## Cases
        if root is on the x+ side (same y coordinates) NW
        if root is on the x- side (same y coordinates) NE
        if root is on the y+ side (same x coordinates) SE
        if root is on the y- side (same x coordinates) NE

        X -> (x-, y+ NW) SE, NE, SE  
        Y -> (x+, y+ NE) SW, NW, SE
        Z -> (x+, y- SE) NW, NW, NE 
        W -> (x-, y- SW) NE, NE, NE

        M -> (x-, NW) SE, NE
        P -> (x+, NE) SW, NW
        R -> (x+, SE) NW, NW
        L -> (x-, SW) NE, NE

        N -> (y+, NW) SE, SE 
        O -> (y+, NE) SW, SE 
        J -> (y-, SE) NW, NE 
        K -> (y-, SW) NE, NE 

        1, N = SE
        2, O = SE, SW
        3 = SW
        4, G, I, M, X = SE, NE
        5, P = SW, NW
        6, K, L, W = NE
        7, E, F, J, Z = NE, NW
        8, R = NW
        9, A = SE, SW, NE
        10, B, C, Y = SE, SW, NW
        11 = SE, NE, NW 
        12, D = SW, NE, NW
        13 = SE, SW, NE, NW

        1 -> SE
        2 -> SE, SW
        3 -> SW
        4 -> SE, NE
        5 -> SW, NW
        6 -> NE
        7 -> NE, NW
        8 -> NW
        9 -> SE, SW, NE *
        10 -> SE, SW, NW *
        11 -> SE, NE, NW *
        12 -> SW, NE, NW *
        13 -> SE, SW, NE, NW * 
        A -> SE, SW, NE 
        B -> SE, SW, NW 
        C -> SE, SW, NW *
        D -> SW, NE, NW *
        E -> NE, NW *
        F -> NE, NW *
        G -> SE, NE *
        I -> SE, NE *
        P -> SW, NW 
        R -> NW
        J -> NE, NW *
        K -> NE
        L -> NE
        M -> SE, NE
        N -> SE
        O -> SE, SW *
        X -> SE, NE *
        Y -> SE, SW, NW *
        Z -> NE, NW *
        W -> NE

        value (x,y) radius r | root's coordinates a, b
        1 -> (a < x-r) && (b > y+r) 
        6 -> (a < x-r) && (b < y-r) 
        4 -> (a < x-r) && (y+r > b > y-r) 
        3 -> (a > x+r) && (b > y+r) 
        8 -> (a > x+r) && (b < y-r) 
        5 -> (a > x+r) && (y+r > b > y-r) 
        2 -> (x-r < a < x+r) && (b > y+r) 
        7 -> (x-r < a < x+r) && (b < y-r) 
        9 -> 
        10 ->
        11 ->
        12 ->
        13 -> Inside the circle


