# MAC
## Compile and Run
Run the following command to compile and run the program:
```
g++ mac.cpp -o mac
./mac
```

To modify the value of `K`, change the constant named `CONST_K` near file head.


## Questions

### 1. Which of the customers has the most items? How many items do they have?
Customer 8 has the most items with 457 items.

### 2. When starting at the leaf level of the tree, which basket of goods takes the most time to scan? How many time slots does it require?
Customer 5 and 9 with 1017 time slots.

### 3. When starting at the root level of the tree, which basket of goods takes the most time to scan? How many time slots does it require?
Customer 8 with 997 time slots.

### 4. When starting at the root level of the tree, which basket of goods takes the least time to scan? How many time slots are needed?
Customer 1 with 35 time slots.

### 5. When starting at the root level of the tree, which basket of goods generates the most collisions during scanning? How many collisions occur?
Customer 8 with 408 collisions.

### 6. When starting at the root level of the tree, which basket of goods generates the highest proportion of successful slots (i.e., efficiency) during scanning?
Customer 8 with 45.8375% efficiency.

## Summary
From the program, we can see that this MAC protocol is using binary search tree. 
For searching, the number of successes is always the same number with the number of items in the bag, and this implies that every item is probed succcessfully in the tree. 
And for searching from leaf, the number of collisions is always 0 since it implies that there is no repeative items in the bag; the number of time slots is always the last item in the bag plus one. 
Compare the efficiency of searching from root and searching from tree from the program output, we can see that almost always the efficiency of latter one is lower, and especially when the item is only a few. As the number of items increase, the efficiency increase for the latter one, but still always lower or equal to the former one. This is reasonable, because the former one is utilizing the characteristic of binary search tree, which is O(log n) for searching, while the latter one is simply O(n) by using a for-loop to traverse every leaf node. Thus, between the two searching methods, the former one is always more preferred for all the test cases.
However, the above is concluded from all the test cases, but does not always apply to every possible bag. For example, if a customer bag contains one of every single item, or rather contains every single item from 0 to n, then the efficiency for searching from leaf would be always 100% since every time the time slots would be n and successes would be n too. 

## Optional Bonus 1
According to the output by the updated version of the program, the level number for producing highest efficiency is increase as the number of items in the bag increase. When there are fewer items in the bag, the collision is lower, and nodes can be succeeded quickly in the tree with fewer time slots (nodes are succeeded without having to go far down the tree), and starting from upper levels can prevent idle nodes (can traverse less virtual nodes). In constrast, when there are more items in the bag, starting from higher level would cause more collision, and the time slots would be increased; starting from lower levels would make fewer collision, and the time slots would be lower, which makes the efficiency higher.

Then, if we imagine the following scenarios:
1. When there is only one item, then start from level 0 which is root is the most efficient.
2. When there is two items, start from level 1 would be the most efficient, since for the best case, each item would succeed in the  virtual node on each side in level 1.

According to the above, we can make a hypothesis: for a bag of `m` items, it would be the most efficient to start from level `n` where `n` is the power of the nearest power of 2 to `m`.

To verify this hypothesis, we look back to the program output. Here, we pick customer 1, 9 and 10 to verify. 
There are 12 items in customer 1's bag, so the nearest power of 2 to 12 is 3 which 2^3 = 8. The result shows the best efficiency is achieved by starting from level 3.
There are 433 items in customer 9's bag, so the nearest power of 2 to 433 is 9 which 2^9 = 512. The result shows the best efficiency is achieved by starting from level 9.
There are 371 items in customer 10's bag, so the nearest power of 2 to 371 is 8 which 2^8 = 256. The result shows the best efficiency is achieved by starting from level 8.



## Program Output

### Basic version output (no longer in code)

```
Customer 1
---- Root ----      
Collisions: 17      
Success: 12
Idle: 6
Time slots: 35      
Efficiency: 34.2857%
---- Leaf ----      
Collisions: 0       
Success: 12
Idle: 1012
Time slots: 1024    
Efficiency: 1.17188%


Customer 2
---- Root ----      
Collisions: 70      
Success: 50
Idle: 21
Time slots: 141
Efficiency: 35.461%
---- Leaf ----
Collisions: 0
Success: 50
Idle: 974
Time slots: 1024
Efficiency: 4.88281%


Customer 3
---- Root ----
Collisions: 164
Success: 132
Idle: 33
Time slots: 329
Efficiency: 40.1216%
---- Leaf ----
Collisions: 0
Success: 132
Idle: 888
Time slots: 1020
Efficiency: 12.9412%


Customer 4
---- Root ----
Collisions: 191
Success: 150
Idle: 42
Time slots: 383
Efficiency: 39.1645%
---- Leaf ----
Collisions: 0
Success: 150
Idle: 871
Time slots: 1021
Efficiency: 14.6915%


Customer 5
---- Root ----
Collisions: 225
Success: 177
Idle: 49
Time slots: 451
Efficiency: 39.2461%
---- Leaf ----
Collisions: 0
Success: 177
Idle: 840
Time slots: 1017
Efficiency: 17.4041%


Customer 6
---- Root ----
Collisions: 378
Success: 329
Idle: 50
Time slots: 757
Efficiency: 43.461%
---- Leaf ----
Collisions: 0
Success: 329
Idle: 695
Time slots: 1024
Efficiency: 32.1289%


Customer 7
---- Root ----
Collisions: 484
Success: 441
Idle: 44
Time slots: 969
Efficiency: 45.5108%
---- Leaf ----
Collisions: 0
Success: 441
Idle: 581
Time slots: 1022
Efficiency: 43.1507%


Customer 8
---- Root ----
Collisions: 498
Success: 457
Idle: 42
Time slots: 997
Efficiency: 45.8375%
---- Leaf ----
Collisions: 0
Success: 457
Idle: 561
Time slots: 1018
Efficiency: 44.8919%


Customer 9
---- Root ----
Collisions: 478
Success: 433
Idle: 46
Time slots: 957
Efficiency: 45.2456%
---- Leaf ----
Collisions: 0
Success: 433
Idle: 584
Time slots: 1017
Efficiency: 42.5762%


Customer 10
---- Root ----
Collisions: 421
Success: 371
Idle: 51
Time slots: 843
Efficiency: 44.0095%
---- Leaf ----
Collisions: 0
Success: 371
Idle: 653
Time slots: 1024
Efficiency: 36.2305%
```

### Optional Bonus 1 version output (shorter version)

```
Customer 1
Highest efficiency result: 
Level n: 3
Collisions: 11
Success: 12
Idle: 7
Time slots: 30
Efficiency: 40%

Customer 2
Highest efficiency result: 
Level n: 6
Collisions: 24
Success: 50
Idle: 38
Time slots: 112
Efficiency: 44.6429%

Customer 3
Highest efficiency result: 
Level n: 7
Collisions: 64
Success: 132
Idle: 60
Time slots: 256
Efficiency: 51.5625%

Customer 4
Highest efficiency result: 
Level n: 7
Collisions: 88
Success: 150
Idle: 66
Time slots: 304
Efficiency: 49.3421%

Customer 5
Highest efficiency result: 
Level n: 7
Collisions: 107
Success: 177
Idle: 58
Time slots: 342
Efficiency: 51.7544%

Customer 6
Highest efficiency result: 
Level n: 8
Collisions: 152
Success: 329
Idle: 79
Time slots: 560
Efficiency: 58.75%

Customer 7
Highest efficiency result: 
Level n: 9
Collisions: 92
Success: 441
Idle: 162
Time slots: 695
Efficiency: 63.4532%

Customer 8
Highest efficiency result: 
Level n: 9
Collisions: 101
Success: 457
Idle: 153
Time slots: 711
Efficiency: 64.2757%       

Customer 9
Highest efficiency result: 
Level n: 9
Collisions: 87
Success: 433
Idle: 163
Time slots: 683
Efficiency: 63.3968%       

Customer 10
Highest efficiency result: 
Level n: 8
Collisions: 189
Success: 371
Idle: 74
Time slots: 634
Efficiency: 58.5174%
```

### Optional Bonus 1 version output (complete version, with every level n result printed)
```
Customer 1    
Level n: 0    
Collisions: 17
Success: 12   
Idle: 6       
Time slots: 35
Efficiency: 34.2857%

Level n: 1
Collisions: 16
Success: 12
Idle: 6
Time slots: 34
Efficiency: 35.2941%

Level n: 2
Collisions: 14
Success: 12
Idle: 6
Time slots: 32
Efficiency: 37.5%

Level n: 3
Collisions: 11
Success: 12
Idle: 7
Time slots: 30
Efficiency: 40%

Level n: 4
Collisions: 8
Success: 12
Idle: 12
Time slots: 32
Efficiency: 37.5%

Level n: 5
Collisions: 5
Success: 12
Idle: 25
Time slots: 42
Efficiency: 28.5714%

Level n: 6
Collisions: 3
Success: 12
Idle: 55
Time slots: 70
Efficiency: 17.1429%

Level n: 7
Collisions: 1
Success: 12
Idle: 117
Time slots: 130
Efficiency: 9.23077%

Level n: 8
Collisions: 0
Success: 12
Idle: 244
Time slots: 256
Efficiency: 4.6875%

Level n: 9
Collisions: 0
Success: 12
Idle: 500
Time slots: 512
Efficiency: 2.34375%

Level n: 10
Collisions: 0
Success: 12
Idle: 1012
Time slots: 1024
Efficiency: 1.17188%

Highest efficiency result:
Level n: 3
Collisions: 11
Success: 12
Idle: 7
Time slots: 30
Efficiency: 40%



Customer 2
Level n: 0
Collisions: 70
Success: 50
Idle: 21
Time slots: 141
Efficiency: 35.461%

Level n: 1
Collisions: 69
Success: 50
Idle: 21
Time slots: 140
Efficiency: 35.7143%

Level n: 2
Collisions: 67
Success: 50
Idle: 21
Time slots: 138
Efficiency: 36.2319%

Level n: 3
Collisions: 63
Success: 50
Idle: 21
Time slots: 134
Efficiency: 37.3134%

Level n: 4
Collisions: 55
Success: 50
Idle: 21
Time slots: 126
Efficiency: 39.6825%

Level n: 5
Collisions: 41
Success: 50
Idle: 23
Time slots: 114
Efficiency: 43.8596%

Level n: 6
Collisions: 24
Success: 50
Idle: 38
Time slots: 112
Efficiency: 44.6429%

Level n: 7
Collisions: 14
Success: 50
Idle: 92
Time slots: 156
Efficiency: 32.0513%

Level n: 8
Collisions: 7
Success: 50
Idle: 213
Time slots: 270
Efficiency: 18.5185%

Level n: 9
Collisions: 1
Success: 50
Idle: 463
Time slots: 514
Efficiency: 9.72763%

Level n: 10
Collisions: 0
Success: 50
Idle: 974
Time slots: 1024
Efficiency: 4.88281%

Highest efficiency result:
Level n: 6
Collisions: 24
Success: 50
Idle: 38
Time slots: 112
Efficiency: 44.6429%



Customer 3
Level n: 0
Collisions: 164
Success: 132
Idle: 33
Time slots: 329
Efficiency: 40.1216%

Level n: 1
Collisions: 163
Success: 132
Idle: 33
Time slots: 328
Efficiency: 40.2439%

Level n: 2
Collisions: 161
Success: 132
Idle: 33
Time slots: 326
Efficiency: 40.4908%

Level n: 3
Collisions: 157
Success: 132
Idle: 33
Time slots: 322
Efficiency: 40.9938%

Level n: 4
Collisions: 149
Success: 132
Idle: 33
Time slots: 314
Efficiency: 42.0382%

Level n: 5
Collisions: 133
Success: 132
Idle: 33
Time slots: 298
Efficiency: 44.2953%

Level n: 6
Collisions: 105
Success: 132
Idle: 37
Time slots: 274
Efficiency: 48.1752%

Level n: 7
Collisions: 64
Success: 132
Idle: 60
Time slots: 256
Efficiency: 51.5625%

Level n: 8
Collisions: 29
Success: 132
Idle: 152
Time slots: 313
Efficiency: 42.1725%

Level n: 9
Collisions: 9
Success: 132
Idle: 387
Time slots: 528
Efficiency: 25%

Level n: 10
Collisions: 0
Success: 132
Idle: 888
Time slots: 1020
Efficiency: 12.9412%

Highest efficiency result:
Level n: 7
Collisions: 64
Success: 132
Idle: 60
Time slots: 256
Efficiency: 51.5625%



Customer 4
Level n: 0
Collisions: 191
Success: 150
Idle: 42
Time slots: 383
Efficiency: 39.1645%

Level n: 1
Collisions: 190
Success: 150
Idle: 42
Time slots: 382
Efficiency: 39.267%

Level n: 2
Collisions: 188
Success: 150
Idle: 42
Time slots: 380
Efficiency: 39.4737%

Level n: 3
Collisions: 184
Success: 150
Idle: 42
Time slots: 376
Efficiency: 39.8936%

Level n: 4
Collisions: 176
Success: 150
Idle: 42
Time slots: 368
Efficiency: 40.7609%

Level n: 5
Collisions: 160
Success: 150
Idle: 42
Time slots: 352
Efficiency: 42.6136%

Level n: 6
Collisions: 130
Success: 150
Idle: 44
Time slots: 324
Efficiency: 46.2963%

Level n: 7
Collisions: 88
Success: 150
Idle: 66
Time slots: 304
Efficiency: 49.3421%

Level n: 8
Collisions: 44
Success: 150
Idle: 150
Time slots: 344
Efficiency: 43.6047%

Level n: 9
Collisions: 14
Success: 150
Idle: 375
Time slots: 539
Efficiency: 27.8293%

Level n: 10
Collisions: 0
Success: 150
Idle: 871
Time slots: 1021
Efficiency: 14.6915%

Highest efficiency result:
Level n: 7
Collisions: 88
Success: 150
Idle: 66
Time slots: 304
Efficiency: 49.3421%



Customer 5
Level n: 0
Collisions: 225
Success: 177
Idle: 49
Time slots: 451
Efficiency: 39.2461%

Level n: 1
Collisions: 224
Success: 177
Idle: 49
Time slots: 450
Efficiency: 39.3333%

Level n: 2
Collisions: 222
Success: 177
Idle: 49
Time slots: 448
Efficiency: 39.5089%

Level n: 3
Collisions: 218
Success: 177
Idle: 49
Time slots: 444
Efficiency: 39.8649%

Level n: 4
Collisions: 210
Success: 177
Idle: 49
Time slots: 436
Efficiency: 40.5963%

Level n: 5
Collisions: 194
Success: 177
Idle: 49
Time slots: 420
Efficiency: 42.1429%

Level n: 6
Collisions: 162
Success: 177
Idle: 49
Time slots: 388
Efficiency: 45.6186%

Level n: 7
Collisions: 107
Success: 177
Idle: 58
Time slots: 342
Efficiency: 51.7544%

Level n: 8
Collisions: 54
Success: 177
Idle: 132
Time slots: 363
Efficiency: 48.7603%

Level n: 9
Collisions: 18
Success: 177
Idle: 350
Time slots: 545
Efficiency: 32.4771%

Level n: 10
Collisions: 0
Success: 177
Idle: 840
Time slots: 1017
Efficiency: 17.4041%

Highest efficiency result:
Level n: 7
Collisions: 107
Success: 177
Idle: 58
Time slots: 342
Efficiency: 51.7544%



Customer 6
Level n: 0
Collisions: 378
Success: 329
Idle: 50
Time slots: 757
Efficiency: 43.461%

Level n: 1
Collisions: 377
Success: 329
Idle: 50
Time slots: 756
Efficiency: 43.5185%

Level n: 2
Collisions: 375
Success: 329
Idle: 50
Time slots: 754
Efficiency: 43.634%

Level n: 3
Collisions: 371
Success: 329
Idle: 50
Time slots: 750
Efficiency: 43.8667%

Level n: 4
Collisions: 363
Success: 329
Idle: 50
Time slots: 742
Efficiency: 44.3396%

Level n: 5
Collisions: 347
Success: 329
Idle: 50
Time slots: 726
Efficiency: 45.3168%

Level n: 6
Collisions: 315
Success: 329
Idle: 50
Time slots: 694
Efficiency: 47.4063%

Level n: 7
Collisions: 254
Success: 329
Idle: 53
Time slots: 636
Efficiency: 51.7296%

Level n: 8
Collisions: 152
Success: 329
Idle: 79
Time slots: 560
Efficiency: 58.75%

Level n: 9
Collisions: 50
Success: 329
Idle: 233
Time slots: 612
Efficiency: 53.7582%

Level n: 10
Collisions: 0
Success: 329
Idle: 695
Time slots: 1024
Efficiency: 32.1289%

Highest efficiency result:
Level n: 8
Collisions: 152
Success: 329
Idle: 79
Time slots: 560
Efficiency: 58.75%



Customer 7
Level n: 0
Collisions: 484
Success: 441
Idle: 44
Time slots: 969
Time slots: 968
Efficiency: 45.5579%

Level n: 2
Collisions: 481
Success: 441
Idle: 44
Time slots: 966
Efficiency: 45.6522%

Level n: 3
Collisions: 477    
Success: 441       
Idle: 44
Time slots: 962    
Efficiency: 45.842%

Level n: 4
Collisions: 469     
Success: 441        
Idle: 44
Time slots: 954     
Efficiency: 46.2264%

Level n: 5
Collisions: 453     
Success: 441        
Idle: 44
Time slots: 938     
Efficiency: 47.0149%

Level n: 6
Collisions: 421     
Success: 441        
Idle: 44
Time slots: 906     
Efficiency: 48.6755%

Level n: 7
Collisions: 357     
Success: 441        
Idle: 44
Time slots: 842     
Efficiency: 52.3753%

Level n: 8
Collisions: 239
Success: 441
Idle: 54
Time slots: 734
Efficiency: 60.0817%

Level n: 9
Collisions: 92
Success: 441
Idle: 162
Time slots: 695
Efficiency: 63.4532%

Level n: 10
Collisions: 0
Success: 441
Idle: 581
Time slots: 1022
Efficiency: 43.1507%

Highest efficiency result:
Level n: 9
Collisions: 92
Success: 441
Idle: 162
Time slots: 695
Efficiency: 63.4532%



Customer 8
Level n: 0
Collisions: 498
Success: 457
Idle: 42
Time slots: 997
Efficiency: 45.8375%

Level n: 1
Collisions: 497
Success: 457
Idle: 42
Time slots: 996
Efficiency: 45.8835%

Level n: 2
Collisions: 495
Success: 457
Idle: 42
Time slots: 994
Efficiency: 45.9759%

Level n: 3
Collisions: 491
Success: 457
Idle: 42
Time slots: 990
Efficiency: 46.1616%

Level n: 4
Collisions: 483
Success: 457
Idle: 42
Time slots: 982
Efficiency: 46.5377%

Level n: 5
Collisions: 467
Success: 457
Idle: 42
Time slots: 966
Efficiency: 47.3085%

Level n: 6
Collisions: 435
Success: 457
Idle: 42
Time slots: 934
Efficiency: 48.9293%

Level n: 7
Collisions: 371
Success: 457
Idle: 42
Time slots: 870
Efficiency: 52.5287%

Level n: 8
Collisions: 255
Success: 457
Idle: 53
Time slots: 765
Efficiency: 59.7386%

Level n: 9
Collisions: 101
Success: 457
Idle: 153
Time slots: 711
Efficiency: 64.2757%

Level n: 10
Collisions: 0
Success: 457
Idle: 561
Time slots: 1018
Efficiency: 44.8919%

Highest efficiency result:
Level n: 9
Collisions: 101
Success: 457
Idle: 153
Time slots: 711
Efficiency: 64.2757%



Customer 9
Level n: 0
Collisions: 478
Success: 433
Idle: 46
Time slots: 957
Efficiency: 45.2456%

Level n: 1
Collisions: 477
Success: 433
Idle: 46
Time slots: 956
Efficiency: 45.2929%

Level n: 2
Collisions: 475
Success: 433
Idle: 46
Time slots: 954
Efficiency: 45.3878%

Level n: 3
Collisions: 471
Success: 433
Idle: 46
Time slots: 950
Efficiency: 45.5789%

Level n: 4
Collisions: 463
Success: 433
Idle: 46
Time slots: 942
Efficiency: 45.966%

Level n: 5
Collisions: 447
Success: 433
Idle: 46
Time slots: 926
Efficiency: 46.7603%

Level n: 6
Collisions: 415
Success: 433
Idle: 46
Time slots: 894
Efficiency: 48.434%

Level n: 7
Collisions: 353
Success: 433
Idle: 48
Time slots: 834
Efficiency: 51.9185%

Level n: 8
Collisions: 236
Success: 433
Idle: 58
Time slots: 727
Efficiency: 59.5598%

Level n: 9
Collisions: 87
Success: 433
Idle: 163
Time slots: 683
Efficiency: 63.3968%

Level n: 10
Collisions: 0
Success: 433
Idle: 584
Time slots: 1017
Efficiency: 42.5762%

Highest efficiency result:
Level n: 9
Collisions: 87
Success: 433
Idle: 163
Time slots: 683
Efficiency: 63.3968%



Customer 10
Level n: 0
Collisions: 421
Success: 371
Idle: 51
Time slots: 843
Efficiency: 44.0095%

Level n: 1
Collisions: 420
Success: 371
Idle: 51
Time slots: 842
Efficiency: 44.0618%

Level n: 2
Collisions: 418
Success: 371
Idle: 51
Time slots: 840
Efficiency: 44.1667%

Level n: 3
Collisions: 414
Success: 371
Idle: 51
Time slots: 836
Efficiency: 44.378%

Level n: 4
Collisions: 406
Success: 371
Idle: 51
Time slots: 828
Efficiency: 44.8068%

Level n: 5
Collisions: 390
Success: 371
Idle: 51
Time slots: 812
Efficiency: 45.6897%

Level n: 6
Collisions: 358
Success: 371
Idle: 51
Time slots: 780
Efficiency: 47.5641%

Level n: 7
Collisions: 295
Success: 371
Idle: 52
Time slots: 718
Efficiency: 51.6713%

Level n: 8
Collisions: 189
Success: 371
Idle: 74
Time slots: 634
Efficiency: 58.5174%

Level n: 9
Collisions: 66
Success: 371
Idle: 207
Time slots: 644
Efficiency: 57.6087%

Level n: 10
Collisions: 0
Success: 371
Idle: 653
Time slots: 1024
Efficiency: 36.2305%

Highest efficiency result:
Level n: 8
Collisions: 189
Success: 371
Idle: 74
Time slots: 634
Efficiency: 58.5174%
```