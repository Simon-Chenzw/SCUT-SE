### 陈卓文 软件工程2班 201936380215
#### 第五章
2. 设4维数组的4个下标的范围分别为[-1,0]，[1,2]，[1,3]，[-2,-1]，请分别按行序和按列序列出各元素。
    * 按行储存： A[-1,1,1,-2], A[-1,1,1,-1], A[-1,1,2,-2], A[-1,1,2,-1], A[-1,1,3,-2], A[-1,1,3,-1], A[-1,2,1,-2], A[-1,2,1,-1], A[-1,2,2,-2], A[-1,2,2,-1], A[-1,2,3,-2], A[-1,2,3,-1], A[0,1,1,-2], A[0,1,1,-1], A[0,1,2,-2], A[0,1,2,-1], A[0,1,3,-2], A[0,1,3,-1], A[0,2,1,-2], A[0,2,1,-1], A[0,2,2,-2], A[0,2,2,-1], A[0,2,3,-2], A[0,2,3,-1]
    * 按列储存： A[-1,1,1,-2], A[0,1,1,-2], A[-1,2,1,-2], A[0,2,1,-2], A[-1,1,2,-2], A[0,1,2,-2], A[-1,2,2,-2], A[0,2,2,-2], A[-1,1,3,-2], A[0,1,3,-2], A[-1,2,3,-2], A[0,2,3,-2], A[-1,1,1,-1], A[0,1,1,-1], A[-1,2,1,-1], A[0,2,1,-1], A[-1,1,2,-1], A[0,1,2,-1], A[-1,2,2,-1], A[0,2,2,-1], A[-1,1,3,-1], A[0,1,3,-1], A[-1,2,3,-1], A[0,2,3,-1]

3. 对上题，分别计算元素 a -1,2,2,-2 的按行存储与按列存储的相对地址（设每个元素占2个单元）
    * 按行 2*(0*2*3*2+1*3*2+1*2+0)=16
    * 按列 2*(0+2*1+2*2*1+2*2*3*0)=12

4. 写出 n 维数组按列存储的寻址公式的计算函数。
    * 设 n 维数组第 k 维的下标范围是[lk, hk]，记 dk = hk - lk + 1，jk = ik - lk，k= 1,2, …, n
    * 设每个元素占 c 个单元
    * Loc(i1,i2, … ,in) = c ·(j1 + d1j2 + d1d2j3 + …+ d1d2 …dn-1jn) 
    * 伪代码为
    ```
        s = 0;
        k = n;
        while ( k >= 1){
            s = s * dk + jk;
            k = k - 1;
        }
    ```
    * C函数为
    ```
        long GetArrayElemAddress(long l[], long h[], long i[], long n, int c){
            long k, s;
            s = 0;
            for (k = n - 1; k >=1 ; k--)
                s = s*(h[k] – l[k] + 1) + (i[k] – l[k]);
            return s;
        }
    ```

6. 分别推导出上三角矩阵按行与按列存储的寻址公式，不妨假设下标范围为 1~n
    * 按行存储 
        * 当 i >= j     Loc(i,j) = c * ((2 * n + 2 - i) * (i - 1) // 2 - i + j)
        * 当 i < j      Loc(i,j) = Loc(j,i)  
    * 按列存储 
        * 当 i >= j     Loc(i,j) = c * ((j - 1) * j // 2 + i - 1)  
        * 当 i < j      Loc(i,j) = Loc(j,i)  

    