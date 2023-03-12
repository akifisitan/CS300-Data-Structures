# LZW - Hash Table Assignment
    initial string is 
    aaabbbbbbaabaaba
    initial dictionary:
    a: 0, b: 1
    begin:
    longest prefix of the string that is in the dictionary: a
    output code of longest prefix which is a: 0
    then insert prefix + prefix + 1 to the dictionary, which is aa
    dictionary:
    a: 0, b: 1, aa: 2
    now the remaining string is (remove longest prefix: a)
    aabbbbbbaabaaba
    -----------------------
    longest prefix of the string that is in the dictionary: aa
    output code of longest prefix which is aa: 2
    insert prefix + prefix + 1 to the dictionary, which is aab
    dictionary:
    a: 0, b: 1, aa: 2, aab: 3
    now the remaining string is (remove longest prefix: aa)
    bbbbbbaabaaba
    -----------------------
    longest prefix of the string that is in the dictionary: b
    output code of longest prefix which is b: 1
    insert longestPrefix + longestPrefix + 1 which is bb: 4
    dictionary:
    a: 0, b: 1, aa:2, aab: 3, bb: 4
    now the remaining string is (remove longest prefix: b)
    bbbbbaabaaba
    ----------------------
    longest prefix of the string that is in the dictionary: bb
    output code of longest prefix which is bb: 4
    insert longestPrefix + longestPrefix + 1 which is bbb: 5
    dictionary:
    a: 0, b: 1, aa:2, aab: 3, bb: 4, bbb: 5
    now the remaining string is (remove longest prefix: bb)
    bbbaabaaba
    ---------------------
    longest prefix of the string that is in the dictionary: bbb
    output code of longest prefix which is bbb: 5
    insert bbba: 6
    dictionary:
    a: 0, b: 1, aa:2, aab: 3, bb: 4, bbb: 5, bbba: 6
    now the remaining string is (remove longest prefix: bbb)
    aabaaba
    --------------------
    longest prefix of the string that is in the dictionary: aab
    output code of longest prefix which is aab: 3
    insert aaba: 7
    dictionary:
    a: 0, b: 1, aa:2, aab: 3, bb: 4, bbb: 5, bbba: 6, aaba: 7
    now the remaining string is (remove longest prefix: aab)
    aaba
    --------------------
    longest prefix of the string that is in the dictionary: aaba
    output code of longest prefix which is aaba: 7 
    End of file reached, return
    dictionary:
    a: 0, b: 1, aa:2, aab: 3, bb: 4, bbb: 5, bbba: 6, aaba: 7
    now the remaining string is (remove longest prefix: aaba)
    empty