# 操作系统实验报告

**学号：** 201220139

**姓名：** 艾泠州

**邮箱：** 201220139@smail.nju.edu.cn

**日期：** 2022年5月16日

------

### 1. Exercises

1. 请回答一下，什么情况下会出现死锁。

   ``` C
   #define N 5                // 哲学家个数
   semaphore fork[5];         // 信号量初值为1
   void philosopher(int i){   // 哲学家编号：0-4
     while(TRUE){
       think();               // 哲学家在思考
       P(fork[i]);            // 去拿左边的叉子
       P(fork[(i+1)%N]);      // 去拿右边的叉子
       eat();                 // 吃面条
       V(fork[i]);            // 放下左边的叉子
       V(fork[(i+1)%N]);      // 放下右边的叉子
     }
   }
   ```
   
   答：当所有哲学家都拿起了左边（或右边）的叉子时，他们都将进入等待右边（或左边）的叉子放下的状态，此时将出现死锁。
   
   
   
2. 说一下该方案有什么不足？（答出一点即可）

   ``` C
   #define N 5                // 哲学家个数
   semaphore fork[5];         // 信号量初值为1
   semaphore mutex;           // 互斥信号量，初值1
   void philosopher(int i){   // 哲学家编号：0-4
     while(TRUE){
       think();               // 哲学家在思考
       P(mutex);              // 进入临界区
       P(fork[i]);            // 去拿左边的叉子
       P(fork[(i+1)%N]);      // 去拿右边的叉子
       eat();                 // 吃面条
       V(fork[i]);            // 放下左边的叉子
       V(fork[(i+1)%N]);      // 放下右边的叉子
       V(mutex);              // 退出临界区
     }
   }
   ```

   答：当其中一名哲学家在吃面条时，程序将一直处于临界区状态，其他结束了思考的哲学家将无法去取身边的叉子。

   

3. 正确且高效的解法有很多，请你利用信号量 PV 操作设计一种正确且相对高效（比方案 2 高效）的哲学家吃饭算法。

   答：如下，在哲学家开始吃面条时退出临界区即可。

   ``` C
   #define N 5                // 哲学家个数
   semaphore fork[5];         // 信号量初值为1
   semaphore mutex;           // 互斥信号量，初值1
   void philosopher(int i){   // 哲学家编号：0-4
     while(TRUE){
       think();               // 哲学家在思考
       P(mutex);              // 进入临界区
       P(fork[i]);            // 去拿左边的叉子
       P(fork[(i+1)%N]);      // 去拿右边的叉子
       V(mutex);              // 退出临界区
       eat();                 // 吃面条
       V(fork[i]);            // 放下左边的叉子
       V(fork[(i+1)%N]);      // 放下右边的叉子
     }
   }
   ```

   

4. 为什么要用两个信号量呢？`emptyBuffers` 和 `fullBuffer` 分别有什么直观含义？

   ``` Java
   class BoundedBuffer {  // buffer
   	mutex = new Semaphore(1);
   	fullBuffers = new Semaphore(0);
   	emptyBuffers = new Semaphore(n);
   }
   
   BoundedBuffer::Deposit(c) {
     emptyBuffers->P();
     mutex->P();
     Add c to the buffer;
     mutex->V();
     fullBuffers->V();
   }
   
   BoundedBuffer::Remove(c) {
     fullBuffers->P();
     mutex->P();
     Remove c from buffer;
     mutex->V();
     emptyBuffers->V();
   }
   ```

   答：因为只有一个信号量时，将无法同时判断缓冲区「是否为空」和「是否为满」。`emptyBuffers` 在缓冲区为空时将处于等待状态，同理 `fullBuffers` 在缓冲区已满时将处于等待状态。




### 2. Tasks

1. 完成格式化输入。

   如下图：

   ![](/home/oslab/图片/2022-05-18 06-17-33 的屏幕截图.png)

2. 实现下面四个函数。

   + `syscallSemInit()`
   + `syscallSemWait()`
   + `syscallSemPost()`
   + `syscallSemDestroy()`

3. 完成 `app` 里面的下列问题，在报告里放上运行截图。

   + 哲学家就餐问题

     ![](/home/oslab/图片/2022-05-18 06-18-54 的屏幕截图.png)

   + 生产者-消费者问题（选做）

     ![](/home/oslab/图片/2022-05-18 06-20-14 的屏幕截图.png)

   + 读者-写者问题（选做）
