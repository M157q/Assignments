##Part A
+ Explain your design and how you solve the synchronization problem in the shared memory version.

    + FIFO & Shared Memory: 
        1. 複製助教給的 fifo 範例 code
        2. 建一個 50x50 的 Map，初始化為 0 代表 available
        3. 用 random 隨機決定一個起始點，由 parent process 先下（將起始點的值設為2; 1則代表 child 下過的地方）。
        4. 開始進行 fork，這部份是直接複製助教給的範例程式碼。
        5. 根據 FIFO 或 SHM，使用不同的程式碼溝通，其實也只是複製助教給的範例程式碼後，再作一點點修改。
        6. 進入 while 迴圈，一直到有其中一方獲勝才會 break 出來。
        7. 在 while 迴圈後 child 和 parent 開始輪流佔點。 FIFO 的話就用助教給的程式碼從 named pipe 讀取上個人下的位置 / SHM 的話就用助教給的程式碼從 shared memory 讀取上個人下的位置。
        8. 每次都會呼叫 play 這個 function，來決定此次要下的位置以及判斷獲勝與否
        9. 一直到有一方獲勝後跳出迴圈 (turn >= 2)
        10. 最後根據 turn 的值，獲勝的一方寫入 1，失敗的一方寫入 0。
        11. FIFO 用助教給的程式碼移除 named pipe / SHM 用助教給的程式碼移除 shared memory
        
   基本上就是用 turn 這個變數來當作 lock 的機制。  
   在 child process 中，child 必須等到 turn 為 0 時，child 才可以執行該回合的動作。  
   在 parent process 中，parent 必須等到 turn 為 1 時，parent 才可以執行該回合的動作。  
	而 turn 這個變數同時也扮演了決定誰獲勝的因素：  
	當 turn 為 2 時，代表 child 獲勝、當 turn 為 3 時代表 parent 獲勝。 

##Part B
+ B.1: What is the purpose of the program? What are the meanings of the output messages?  
Ans:  
比較四種不同的 memory control，Single Process 及 Dual Process 各兩種。  
    + 第一種為 Single Process 但並未使用 memcpy。  
    + 第二種為 Single Process 並使用 memcpy。  
    + 第三種為 Dual Process 並使用 shmget 後利用 systemV shared memory segment 進行 memory control。
測試這四種不同的 memory control 方法，在 allocates 並寫入相同大小及次數的 memory 後所經過的時間。
Output message 的便是顯示其經過的時間，進而比較時間上的差異。
    + 第四種為 Dual Process 並使用 shm_open 後利用 mmap 進行 memory control。  
    

+ B.2: Tweak BUF_SIZE (in shared_mem.cpp) to `1024*1024*60` and redo the experiments. Describe your findings and explain the cause.  
Ans:  
    + -DSIGNLE: `Duration : 120.633 seconds`
    + -DCOPY: `Duration : 314.058 seconds`
    + -DSHM: 

    ```
    SHM_SIZE = 251658240  
    Using System V shared memory segment
    a.out: shared_mem.cpp:144: void TwoProcess(): Assertion 'sid !=-1' failed.
    Command terminated
    ```
    
    + -DMMAP: 
    
    ```
    SHM_SIZE = 251658240
    Using mmap
    BUF_X at 0x7f75a52c2000
    BUF_Y at 0x7f75962c2000
    Duration : 128.008 seconds
    ```

除了 -DSHM 以外，其他三種的時間都大概是先前的十倍左右，可以合理猜測其執行時間是跟 memory size 呈線性的關係。  
而 -DSHM 的部份似乎是因為 memory size 過大而在 assert 的地方 break 了。  
`$man shmget` 之後，裡面有寫到

```
SHMALL System wide maximum of shared memory pages 
(on Linux, this limit can be read and modified 
via /proc/sys/kernel/shmall).
```

251658240 很明顯超過了`/proc/sys/kernel/shmall`中的大小了，所以 shmget 無法要到想要的 memory size，所以 sid 當然就是 -1 了。


+ B.3: What are the technical differences between using -DSINGLE and -DCOPY?  
Ans:  
    + -DSINGLE 只使用 Single Process，並直接使用 BUF_Y = BUF_X 將 X 的內容複製到 BUF_Y。    
    + -DCOPY 同樣也是使用 Single Process 但是使用了 memcpy 將 BUF_X 的內容複製到 BUF_Y。

+ B.4: What are the technical differences between using -DSINGLE and -DSHM?  
Ans:  
    + -DSINGLE 為 Single Process。  
    + -DSHM 為 Dual Process。  

+ B.5: What are the technical differences between using -DSHM and -DMMAP?  
Ans:  
    + -DSHM 為 Dual Process，並使用了 shmget 利用 systemV shared memory segment 作記憶體的管理。
    + -DMMAP 同樣也為 Dual Process，和 -DSHM 不同的是，其利用了 shm_open 利用 mmap 作記憶體的管理。

