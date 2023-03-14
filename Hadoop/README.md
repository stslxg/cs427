# Hadoop MapReduce 作业说明
黄炫圭

5100309715

-----
## 概述
在这个作业中，我使用了HadoopStreaming运行Python程序，计算PageRank。

## 文件树
    -+---- README.md           说明文件
     |---- README.html         说明文件
     |---- copy_input.sh       从/media/tmp/wiki/enwiki复制原始数据到HDFS的/user/huangxuangui/in目录下
     |---- remove_output.sh    递归调用各个step的remove_output.sh，删除HDFS中计算得到的数据
     |---- test.sh             递归调用各个step的test.sh，进行小数据的测试
     |---- run.sh              递归调用各个step的run.sh，进行完整的PageRank计算
     |-+-- step1               第一步，从数据的title域中获取页面名字，从text域中parse出包含在[[]]中的链接，并进行一定处理
     | |-- remove_output.sh    删除HDFS及本地中计算得到的数据
     | |-- test.sh             只用wiki_0.txt进行小数据测试
     | |-- run.sh              用全部数据进行parse
     | --- mapper.py           第一步使用的parser，生成包含初始PageRank的正向链接表
     |-+-- step2               第二步，迭代计算PageRank
     | |-- remove_output.sh    删除HDFS及本地中计算得到的数据
     | |-- test.sh             进行小数据测试
     | |-- run.sh              用全部数据进行计算，总共迭代5次
     | |-- mapper.py           将正向链接转换为反向链接，并附上链出页面PageRank和链出数目，以及链入页面原始PageRank
     | |-- reducer.py          计算新的PageRank, 生成新的反向链接表
     | |-- mapper2.py          将反向链接转换为正向链接
     | --- reducer2.py         生成新的包含PageRank的正向链接表
     --+-- step3               第三步，利用Hadoop MapReduce自带的从小到大sort进行排序
       |-- remove_output.sh    删除HDFS及本地中计算得到的数据
       |-- test.sh             进行小数据测试
       |-- run.sh              用全部数据进行计算
       |-- mapper.py           将用大数减过的PageRank作为Key，页面名字作为value
       --- reducer.py          恢复页面名字-PageRank作为Key-Value对
## 运行结果
最终运行结果可以在HDFS下`/user/huangxuangui/out`下获取。以下为整个运行过程（一共有五次迭代）的console输出，从中可以看出总共需要1小时8分钟左右的时间：
```
13/11/26 14:39:39 WARN conf.Configuration: mapred.reduce.tasks is deprecated. Instead, use mapreduce.job.reduces
packageJobJar: [/srv/hadoop/hadoop/hadoop-unjar5097673904250456430/] [] /tmp/streamjob5949204282942779634.jar tmpDir=null
13/11/26 14:39:39 INFO service.AbstractService: Service:org.apache.hadoop.yarn.client.YarnClientImpl is inited.
13/11/26 14:39:39 INFO service.AbstractService: Service:org.apache.hadoop.yarn.client.YarnClientImpl is started.
13/11/26 14:39:39 INFO service.AbstractService: Service:org.apache.hadoop.yarn.client.YarnClientImpl is inited.
13/11/26 14:39:39 INFO service.AbstractService: Service:org.apache.hadoop.yarn.client.YarnClientImpl is started.
13/11/26 14:39:40 INFO mapred.FileInputFormat: Total input paths to process : 391
13/11/26 14:39:40 INFO mapreduce.JobSubmitter: number of splits:391
13/11/26 14:39:40 WARN conf.Configuration: mapred.jar is deprecated. Instead, use mapreduce.job.jar
13/11/26 14:39:40 WARN conf.Configuration: mapred.cache.files is deprecated. Instead, use mapreduce.job.cache.files
13/11/26 14:39:40 WARN conf.Configuration: mapred.mapoutput.value.class is deprecated. Instead, use mapreduce.map.output.value.class
13/11/26 14:39:40 WARN conf.Configuration: mapred.used.genericoptionsparser is deprecated. Instead, use mapreduce.client.genericoptionsparser.used
13/11/26 14:39:40 WARN conf.Configuration: mapred.job.name is deprecated. Instead, use mapreduce.job.name
13/11/26 14:39:40 WARN conf.Configuration: mapred.input.dir is deprecated. Instead, use mapreduce.input.fileinputformat.inputdir
13/11/26 14:39:40 WARN conf.Configuration: mapred.output.dir is deprecated. Instead, use mapreduce.output.fileoutputformat.outputdir
13/11/26 14:39:40 WARN conf.Configuration: mapred.map.tasks is deprecated. Instead, use mapreduce.job.maps
13/11/26 14:39:40 WARN conf.Configuration: mapred.cache.files.timestamps is deprecated. Instead, use mapreduce.job.cache.files.timestamps
13/11/26 14:39:40 WARN conf.Configuration: mapred.mapoutput.key.class is deprecated. Instead, use mapreduce.map.output.key.class
13/11/26 14:39:40 WARN conf.Configuration: mapred.working.dir is deprecated. Instead, use mapreduce.job.working.dir
13/11/26 14:39:40 INFO mapreduce.JobSubmitter: Submitting tokens for job: job_1384176415098_0174
13/11/26 14:39:41 INFO client.YarnClientImpl: Submitted application application_1384176415098_0174 to ResourceManager at workstation/192.168.1.150:8032
13/11/26 14:39:41 INFO mapreduce.Job: The url to track the job: http://workstation.mshome.net:8043/proxy/application_1384176415098_0174/
13/11/26 14:39:41 INFO mapreduce.Job: Running job: job_1384176415098_0174
13/11/26 14:39:45 INFO mapreduce.Job: Job job_1384176415098_0174 running in uber mode : false
13/11/26 14:39:45 INFO mapreduce.Job:  map 0% reduce 0%
13/11/26 14:39:59 INFO mapreduce.Job:  map 2% reduce 0%
13/11/26 14:40:00 INFO mapreduce.Job:  map 4% reduce 0%
13/11/26 14:40:01 INFO mapreduce.Job:  map 5% reduce 0%
13/11/26 14:40:02 INFO mapreduce.Job:  map 6% reduce 0%
13/11/26 14:40:11 INFO mapreduce.Job:  map 7% reduce 0%
13/11/26 14:40:12 INFO mapreduce.Job:  map 8% reduce 0%
13/11/26 14:40:13 INFO mapreduce.Job:  map 9% reduce 0%
13/11/26 14:40:14 INFO mapreduce.Job:  map 10% reduce 0%
13/11/26 14:40:15 INFO mapreduce.Job:  map 11% reduce 0%
13/11/26 14:40:16 INFO mapreduce.Job:  map 12% reduce 0%
13/11/26 14:40:21 INFO mapreduce.Job:  map 13% reduce 0%
13/11/26 14:40:22 INFO mapreduce.Job:  map 14% reduce 0%
13/11/26 14:40:24 INFO mapreduce.Job:  map 15% reduce 0%
13/11/26 14:40:25 INFO mapreduce.Job:  map 15% reduce 1%
13/11/26 14:40:28 INFO mapreduce.Job:  map 16% reduce 1%
13/11/26 14:40:29 INFO mapreduce.Job:  map 17% reduce 1%
13/11/26 14:40:31 INFO mapreduce.Job:  map 18% reduce 1%
13/11/26 14:40:33 INFO mapreduce.Job:  map 19% reduce 1%
13/11/26 14:40:35 INFO mapreduce.Job:  map 20% reduce 1%
13/11/26 14:40:36 INFO mapreduce.Job:  map 20% reduce 2%
13/11/26 14:40:40 INFO mapreduce.Job:  map 21% reduce 2%
13/11/26 14:40:41 INFO mapreduce.Job:  map 22% reduce 2%
13/11/26 14:40:42 INFO mapreduce.Job:  map 23% reduce 2%
13/11/26 14:40:43 INFO mapreduce.Job:  map 24% reduce 2%
13/11/26 14:40:44 INFO mapreduce.Job:  map 25% reduce 2%
13/11/26 14:40:45 INFO mapreduce.Job:  map 25% reduce 3%
13/11/26 14:40:51 INFO mapreduce.Job:  map 26% reduce 3%
13/11/26 14:40:52 INFO mapreduce.Job:  map 27% reduce 4%
13/11/26 14:40:53 INFO mapreduce.Job:  map 28% reduce 4%
13/11/26 14:40:55 INFO mapreduce.Job:  map 28% reduce 5%
13/11/26 14:40:56 INFO mapreduce.Job:  map 29% reduce 5%
13/11/26 14:40:57 INFO mapreduce.Job:  map 30% reduce 5%
13/11/26 14:40:59 INFO mapreduce.Job:  map 31% reduce 5%
13/11/26 14:41:03 INFO mapreduce.Job:  map 32% reduce 5%
13/11/26 14:41:04 INFO mapreduce.Job:  map 33% reduce 5%
13/11/26 14:41:05 INFO mapreduce.Job:  map 34% reduce 5%
13/11/26 14:41:06 INFO mapreduce.Job:  map 34% reduce 7%
13/11/26 14:41:07 INFO mapreduce.Job:  map 35% reduce 7%
13/11/26 14:41:08 INFO mapreduce.Job:  map 35% reduce 8%
13/11/26 14:41:12 INFO mapreduce.Job:  map 37% reduce 8%
13/11/26 14:41:13 INFO mapreduce.Job:  map 38% reduce 8%
13/11/26 14:41:16 INFO mapreduce.Job:  map 39% reduce 9%
13/11/26 14:41:20 INFO mapreduce.Job:  map 40% reduce 9%
13/11/26 14:41:21 INFO mapreduce.Job:  map 41% reduce 11%
13/11/26 14:41:23 INFO mapreduce.Job:  map 42% reduce 11%
13/11/26 14:41:25 INFO mapreduce.Job:  map 42% reduce 12%
13/11/26 14:41:26 INFO mapreduce.Job:  map 43% reduce 12%
13/11/26 14:41:28 INFO mapreduce.Job:  map 44% reduce 12%
13/11/26 14:41:30 INFO mapreduce.Job:  map 45% reduce 12%
13/11/26 14:41:33 INFO mapreduce.Job:  map 46% reduce 15%
13/11/26 14:41:34 INFO mapreduce.Job:  map 47% reduce 15%
13/11/26 14:41:36 INFO mapreduce.Job:  map 48% reduce 16%
13/11/26 14:41:39 INFO mapreduce.Job:  map 49% reduce 16%
13/11/26 14:41:41 INFO mapreduce.Job:  map 50% reduce 16%
13/11/26 14:41:43 INFO mapreduce.Job:  map 51% reduce 17%
13/11/26 14:41:46 INFO mapreduce.Job:  map 52% reduce 17%
13/11/26 14:41:48 INFO mapreduce.Job:  map 53% reduce 17%
13/11/26 14:41:49 INFO mapreduce.Job:  map 54% reduce 17%
13/11/26 14:41:50 INFO mapreduce.Job:  map 54% reduce 18%
13/11/26 14:41:53 INFO mapreduce.Job:  map 55% reduce 18%
13/11/26 14:41:55 INFO mapreduce.Job:  map 57% reduce 19%
13/11/26 14:41:58 INFO mapreduce.Job:  map 58% reduce 19%
13/11/26 14:42:01 INFO mapreduce.Job:  map 59% reduce 19%
13/11/26 14:42:02 INFO mapreduce.Job:  map 60% reduce 19%
13/11/26 14:42:03 INFO mapreduce.Job:  map 60% reduce 20%
13/11/26 14:42:04 INFO mapreduce.Job:  map 61% reduce 20%
13/11/26 14:42:07 INFO mapreduce.Job:  map 62% reduce 20%
13/11/26 14:42:10 INFO mapreduce.Job:  map 63% reduce 21%
13/11/26 14:42:13 INFO mapreduce.Job:  map 64% reduce 21%
13/11/26 14:42:15 INFO mapreduce.Job:  map 65% reduce 21%
13/11/26 14:42:17 INFO mapreduce.Job:  map 66% reduce 22%
13/11/26 14:42:19 INFO mapreduce.Job:  map 67% reduce 22%
13/11/26 14:42:21 INFO mapreduce.Job:  map 68% reduce 22%
13/11/26 14:42:23 INFO mapreduce.Job:  map 69% reduce 23%
13/11/26 14:42:25 INFO mapreduce.Job:  map 70% reduce 23%
13/11/26 14:42:27 INFO mapreduce.Job:  map 71% reduce 23%
13/11/26 14:42:29 INFO mapreduce.Job:  map 72% reduce 23%
13/11/26 14:42:30 INFO mapreduce.Job:  map 72% reduce 24%
13/11/26 14:42:32 INFO mapreduce.Job:  map 73% reduce 24%
13/11/26 14:42:34 INFO mapreduce.Job:  map 74% reduce 24%
13/11/26 14:42:36 INFO mapreduce.Job:  map 75% reduce 25%
13/11/26 14:42:38 INFO mapreduce.Job:  map 76% reduce 25%
13/11/26 14:42:40 INFO mapreduce.Job:  map 77% reduce 25%
13/11/26 14:42:42 INFO mapreduce.Job:  map 78% reduce 25%
13/11/26 14:42:43 INFO mapreduce.Job:  map 78% reduce 26%
13/11/26 14:42:44 INFO mapreduce.Job:  map 79% reduce 26%
13/11/26 14:42:47 INFO mapreduce.Job:  map 80% reduce 26%
13/11/26 14:42:48 INFO mapreduce.Job:  map 81% reduce 26%
13/11/26 14:42:49 INFO mapreduce.Job:  map 81% reduce 27%
13/11/26 14:42:50 INFO mapreduce.Job:  map 82% reduce 27%
13/11/26 14:42:53 INFO mapreduce.Job:  map 83% reduce 27%
13/11/26 14:42:54 INFO mapreduce.Job:  map 84% reduce 27%
13/11/26 14:42:56 INFO mapreduce.Job:  map 84% reduce 28%
13/11/26 14:42:57 INFO mapreduce.Job:  map 85% reduce 28%
13/11/26 14:43:01 INFO mapreduce.Job:  map 86% reduce 28%
13/11/26 14:43:02 INFO mapreduce.Job:  map 87% reduce 29%
13/11/26 14:43:03 INFO mapreduce.Job:  map 88% reduce 29%
13/11/26 14:43:09 INFO mapreduce.Job:  map 89% reduce 29%
13/11/26 14:43:10 INFO mapreduce.Job:  map 91% reduce 29%
13/11/26 14:43:11 INFO mapreduce.Job:  map 91% reduce 30%
13/11/26 14:43:15 INFO mapreduce.Job:  map 92% reduce 30%
13/11/26 14:43:16 INFO mapreduce.Job:  map 93% reduce 30%
13/11/26 14:43:17 INFO mapreduce.Job:  map 94% reduce 31%
13/11/26 14:43:19 INFO mapreduce.Job:  map 95% reduce 31%
13/11/26 14:43:21 INFO mapreduce.Job:  map 95% reduce 32%
13/11/26 14:43:23 INFO mapreduce.Job:  map 96% reduce 32%
13/11/26 14:43:24 INFO mapreduce.Job:  map 97% reduce 32%
13/11/26 14:43:27 INFO mapreduce.Job:  map 98% reduce 32%
13/11/26 14:43:29 INFO mapreduce.Job:  map 99% reduce 33%
13/11/26 14:43:30 INFO mapreduce.Job:  map 100% reduce 33%
13/11/26 14:43:36 INFO mapreduce.Job:  map 100% reduce 35%
13/11/26 14:43:39 INFO mapreduce.Job:  map 100% reduce 50%
13/11/26 14:43:41 INFO mapreduce.Job:  map 100% reduce 68%
13/11/26 14:43:42 INFO mapreduce.Job:  map 100% reduce 69%
13/11/26 14:43:45 INFO mapreduce.Job:  map 100% reduce 70%
13/11/26 14:43:48 INFO mapreduce.Job:  map 100% reduce 71%
13/11/26 14:43:50 INFO mapreduce.Job:  map 100% reduce 72%
13/11/26 14:43:54 INFO mapreduce.Job:  map 100% reduce 73%
13/11/26 14:43:56 INFO mapreduce.Job:  map 100% reduce 74%
13/11/26 14:43:58 INFO mapreduce.Job:  map 100% reduce 75%
13/11/26 14:44:00 INFO mapreduce.Job:  map 100% reduce 76%
13/11/26 14:44:03 INFO mapreduce.Job:  map 100% reduce 77%
13/11/26 14:44:06 INFO mapreduce.Job:  map 100% reduce 78%
13/11/26 14:44:09 INFO mapreduce.Job:  map 100% reduce 79%
13/11/26 14:44:12 INFO mapreduce.Job:  map 100% reduce 80%
13/11/26 14:44:14 INFO mapreduce.Job:  map 100% reduce 81%
13/11/26 14:44:15 INFO mapreduce.Job:  map 100% reduce 82%
13/11/26 14:44:19 INFO mapreduce.Job:  map 100% reduce 83%
13/11/26 14:44:21 INFO mapreduce.Job:  map 100% reduce 84%
13/11/26 14:44:24 INFO mapreduce.Job:  map 100% reduce 85%
13/11/26 14:44:27 INFO mapreduce.Job:  map 100% reduce 86%
13/11/26 14:44:30 INFO mapreduce.Job:  map 100% reduce 87%
13/11/26 14:44:31 INFO mapreduce.Job:  map 100% reduce 88%
13/11/26 14:44:34 INFO mapreduce.Job:  map 100% reduce 89%
13/11/26 14:44:37 INFO mapreduce.Job:  map 100% reduce 90%
13/11/26 14:44:40 INFO mapreduce.Job:  map 100% reduce 91%
13/11/26 14:44:42 INFO mapreduce.Job:  map 100% reduce 92%
13/11/26 14:44:45 INFO mapreduce.Job:  map 100% reduce 93%
13/11/26 14:44:48 INFO mapreduce.Job:  map 100% reduce 94%
13/11/26 14:44:50 INFO mapreduce.Job:  map 100% reduce 95%
13/11/26 14:44:52 INFO mapreduce.Job:  map 100% reduce 96%
13/11/26 14:44:54 INFO mapreduce.Job:  map 100% reduce 97%
13/11/26 14:44:58 INFO mapreduce.Job:  map 100% reduce 98%
13/11/26 14:45:00 INFO mapreduce.Job:  map 100% reduce 99%
13/11/26 14:45:03 INFO mapreduce.Job:  map 100% reduce 100%
13/11/26 14:45:05 INFO mapreduce.Job: Job job_1384176415098_0174 completed successfully
13/11/26 14:45:05 INFO mapreduce.Job: Counters: 43
	File System Counters
		FILE: Number of bytes read=1830570572
		FILE: Number of bytes written=3691230031
		FILE: Number of read operations=0
		FILE: Number of large read operations=0
		FILE: Number of write operations=0
		HDFS: Number of bytes read=12294783446
		HDFS: Number of bytes written=1813546056
		HDFS: Number of read operations=1191
		HDFS: Number of large read operations=0
		HDFS: Number of write operations=12
	Job Counters 
		Launched map tasks=391
		Launched reduce tasks=6
		Rack-local map tasks=391
		Total time spent by all maps in occupied slots (ms)=5979724
		Total time spent by all reduces in occupied slots (ms)=4576803
	Map-Reduce Framework
		Map input records=5365743
		Map output records=5365743
		Map output bytes=1816687025
		Map output materialized bytes=1830584612
		Input split bytes=42900
		Combine input records=0
		Combine output records=0
		Reduce input groups=5365743
		Reduce shuffle bytes=1830584612
		Reduce input records=5365743
		Reduce output records=5365743
		Spilled Records=10731486
		Shuffled Maps =2346
		Failed Shuffles=0
		Merged Map outputs=2346
		GC time elapsed (ms)=23291
		CPU time spent (ms)=1087300
		Physical memory (bytes) snapshot=123520569344
		Virtual memory (bytes) snapshot=643189444608
		Total committed heap usage (bytes)=154809532416
	Shuffle Errors
		BAD_ID=0
		CONNECTION=0
		IO_ERROR=0
		WRONG_LENGTH=0
		WRONG_MAP=0
		WRONG_REDUCE=0
	File Input Format Counters 
		Bytes Read=12294740546
	File Output Format Counters 
		Bytes Written=1813546056
13/11/26 14:45:05 INFO streaming.StreamJob: Output directory: /user/huangxuangui/step1/out
13/11/26 14:45:06 WARN conf.Configuration: mapred.reduce.tasks is deprecated. Instead, use mapreduce.job.reduces
packageJobJar: [/srv/hadoop/hadoop/hadoop-unjar5561665067942429988/] [] /tmp/streamjob7214776150738720590.jar tmpDir=null
13/11/26 14:45:07 INFO service.AbstractService: Service:org.apache.hadoop.yarn.client.YarnClientImpl is inited.
13/11/26 14:45:07 INFO service.AbstractService: Service:org.apache.hadoop.yarn.client.YarnClientImpl is started.
13/11/26 14:45:07 INFO service.AbstractService: Service:org.apache.hadoop.yarn.client.YarnClientImpl is inited.
13/11/26 14:45:07 INFO service.AbstractService: Service:org.apache.hadoop.yarn.client.YarnClientImpl is started.
13/11/26 14:45:07 INFO mapred.FileInputFormat: Total input paths to process : 6
13/11/26 14:45:07 INFO mapreduce.JobSubmitter: number of splits:30
13/11/26 14:45:07 WARN conf.Configuration: mapred.jar is deprecated. Instead, use mapreduce.job.jar
13/11/26 14:45:07 WARN conf.Configuration: mapred.cache.files is deprecated. Instead, use mapreduce.job.cache.files
13/11/26 14:45:07 WARN conf.Configuration: mapred.output.value.class is deprecated. Instead, use mapreduce.job.output.value.class
13/11/26 14:45:07 WARN conf.Configuration: mapred.mapoutput.value.class is deprecated. Instead, use mapreduce.map.output.value.class
13/11/26 14:45:07 WARN conf.Configuration: mapred.used.genericoptionsparser is deprecated. Instead, use mapreduce.client.genericoptionsparser.used
13/11/26 14:45:07 WARN conf.Configuration: mapred.job.name is deprecated. Instead, use mapreduce.job.name
13/11/26 14:45:07 WARN conf.Configuration: mapred.input.dir is deprecated. Instead, use mapreduce.input.fileinputformat.inputdir
13/11/26 14:45:07 WARN conf.Configuration: mapred.output.dir is deprecated. Instead, use mapreduce.output.fileoutputformat.outputdir
13/11/26 14:45:07 WARN conf.Configuration: mapred.map.tasks is deprecated. Instead, use mapreduce.job.maps
13/11/26 14:45:07 WARN conf.Configuration: mapred.cache.files.timestamps is deprecated. Instead, use mapreduce.job.cache.files.timestamps
13/11/26 14:45:07 WARN conf.Configuration: mapred.output.key.class is deprecated. Instead, use mapreduce.job.output.key.class
13/11/26 14:45:07 WARN conf.Configuration: mapred.mapoutput.key.class is deprecated. Instead, use mapreduce.map.output.key.class
13/11/26 14:45:07 WARN conf.Configuration: mapred.working.dir is deprecated. Instead, use mapreduce.job.working.dir
13/11/26 14:45:07 INFO mapreduce.JobSubmitter: Submitting tokens for job: job_1384176415098_0175
13/11/26 14:45:08 INFO client.YarnClientImpl: Submitted application application_1384176415098_0175 to ResourceManager at workstation/192.168.1.150:8032
13/11/26 14:45:08 INFO mapreduce.Job: The url to track the job: http://workstation.mshome.net:8043/proxy/application_1384176415098_0175/
13/11/26 14:45:08 INFO mapreduce.Job: Running job: job_1384176415098_0175
13/11/26 14:45:13 INFO mapreduce.Job: Job job_1384176415098_0175 running in uber mode : false
13/11/26 14:45:13 INFO mapreduce.Job:  map 0% reduce 0%
13/11/26 14:45:26 INFO mapreduce.Job:  map 1% reduce 0%
13/11/26 14:45:27 INFO mapreduce.Job:  map 7% reduce 0%
13/11/26 14:45:28 INFO mapreduce.Job:  map 8% reduce 0%
13/11/26 14:45:29 INFO mapreduce.Job:  map 9% reduce 0%
13/11/26 14:45:30 INFO mapreduce.Job:  map 13% reduce 0%
13/11/26 14:45:31 INFO mapreduce.Job:  map 14% reduce 0%
13/11/26 14:45:33 INFO mapreduce.Job:  map 17% reduce 0%
13/11/26 14:45:34 INFO mapreduce.Job:  map 18% reduce 0%
13/11/26 14:45:36 INFO mapreduce.Job:  map 19% reduce 0%
13/11/26 14:45:37 INFO mapreduce.Job:  map 20% reduce 0%
13/11/26 14:45:39 INFO mapreduce.Job:  map 21% reduce 0%
13/11/26 14:45:42 INFO mapreduce.Job:  map 24% reduce 0%
13/11/26 14:45:43 INFO mapreduce.Job:  map 25% reduce 0%
13/11/26 14:45:45 INFO mapreduce.Job:  map 27% reduce 0%
13/11/26 14:45:46 INFO mapreduce.Job:  map 30% reduce 0%
13/11/26 14:45:49 INFO mapreduce.Job:  map 34% reduce 0%
13/11/26 14:45:52 INFO mapreduce.Job:  map 37% reduce 0%
13/11/26 14:45:55 INFO mapreduce.Job:  map 39% reduce 0%
13/11/26 14:45:56 INFO mapreduce.Job:  map 40% reduce 0%
13/11/26 14:45:58 INFO mapreduce.Job:  map 43% reduce 0%
13/11/26 14:46:02 INFO mapreduce.Job:  map 46% reduce 0%
13/11/26 14:46:03 INFO mapreduce.Job:  map 47% reduce 0%
13/11/26 14:46:05 INFO mapreduce.Job:  map 48% reduce 0%
13/11/26 14:46:06 INFO mapreduce.Job:  map 50% reduce 0%
13/11/26 14:46:08 INFO mapreduce.Job:  map 51% reduce 0%
13/11/26 14:46:09 INFO mapreduce.Job:  map 52% reduce 0%
13/11/26 14:46:11 INFO mapreduce.Job:  map 54% reduce 0%
13/11/26 14:46:12 INFO mapreduce.Job:  map 56% reduce 0%
13/11/26 14:46:15 INFO mapreduce.Job:  map 59% reduce 0%
13/11/26 14:46:16 INFO mapreduce.Job:  map 60% reduce 0%
13/11/26 14:46:18 INFO mapreduce.Job:  map 65% reduce 0%
13/11/26 14:46:19 INFO mapreduce.Job:  map 67% reduce 0%
13/11/26 14:46:27 INFO mapreduce.Job:  map 76% reduce 0%
13/11/26 14:46:30 INFO mapreduce.Job:  map 78% reduce 0%
13/11/26 14:46:35 INFO mapreduce.Job:  map 79% reduce 0%
13/11/26 14:46:38 INFO mapreduce.Job:  map 80% reduce 2%
13/11/26 14:46:39 INFO mapreduce.Job:  map 80% reduce 3%
13/11/26 14:46:41 INFO mapreduce.Job:  map 81% reduce 3%
13/11/26 14:46:42 INFO mapreduce.Job:  map 81% reduce 4%
13/11/26 14:46:44 INFO mapreduce.Job:  map 84% reduce 4%
13/11/26 14:46:45 INFO mapreduce.Job:  map 84% reduce 6%
13/11/26 14:46:46 INFO mapreduce.Job:  map 85% reduce 10%
13/11/26 14:46:47 INFO mapreduce.Job:  map 88% reduce 10%
13/11/26 14:46:48 INFO mapreduce.Job:  map 88% reduce 12%
13/11/26 14:46:50 INFO mapreduce.Job:  map 91% reduce 13%
13/11/26 14:46:53 INFO mapreduce.Job:  map 94% reduce 14%
13/11/26 14:46:56 INFO mapreduce.Job:  map 95% reduce 14%
13/11/26 14:46:57 INFO mapreduce.Job:  map 95% reduce 16%
13/11/26 14:46:59 INFO mapreduce.Job:  map 98% reduce 16%
13/11/26 14:47:03 INFO mapreduce.Job:  map 99% reduce 16%
13/11/26 14:47:06 INFO mapreduce.Job:  map 100% reduce 17%
13/11/26 14:47:09 INFO mapreduce.Job:  map 100% reduce 18%
13/11/26 14:47:12 INFO mapreduce.Job:  map 100% reduce 19%
13/11/26 14:47:22 INFO mapreduce.Job:  map 100% reduce 20%
13/11/26 14:47:27 INFO mapreduce.Job:  map 100% reduce 21%
13/11/26 14:47:34 INFO mapreduce.Job:  map 100% reduce 22%
13/11/26 14:47:36 INFO mapreduce.Job:  map 100% reduce 24%
13/11/26 14:47:39 INFO mapreduce.Job:  map 100% reduce 26%
13/11/26 14:47:40 INFO mapreduce.Job:  map 100% reduce 27%
13/11/26 14:47:42 INFO mapreduce.Job:  map 100% reduce 28%
13/11/26 14:47:45 INFO mapreduce.Job:  map 100% reduce 29%
13/11/26 14:47:53 INFO mapreduce.Job:  map 100% reduce 30%
13/11/26 14:48:06 INFO mapreduce.Job:  map 100% reduce 31%
13/11/26 14:48:18 INFO mapreduce.Job:  map 100% reduce 32%
13/11/26 14:48:30 INFO mapreduce.Job:  map 100% reduce 33%
13/11/26 14:48:43 INFO mapreduce.Job:  map 100% reduce 34%
13/11/26 14:48:58 INFO mapreduce.Job:  map 100% reduce 35%
13/11/26 14:49:08 INFO mapreduce.Job:  map 100% reduce 36%
13/11/26 14:49:21 INFO mapreduce.Job:  map 100% reduce 37%
13/11/26 14:49:35 INFO mapreduce.Job:  map 100% reduce 38%
13/11/26 14:49:50 INFO mapreduce.Job:  map 100% reduce 39%
13/11/26 14:49:59 INFO mapreduce.Job:  map 100% reduce 40%
13/11/26 14:50:02 INFO mapreduce.Job:  map 100% reduce 41%
13/11/26 14:50:05 INFO mapreduce.Job:  map 100% reduce 43%
13/11/26 14:50:08 INFO mapreduce.Job:  map 100% reduce 44%
13/11/26 14:50:17 INFO mapreduce.Job:  map 100% reduce 45%
13/11/26 14:50:27 INFO mapreduce.Job:  map 100% reduce 46%
13/11/26 14:50:36 INFO mapreduce.Job:  map 100% reduce 47%
13/11/26 14:50:39 INFO mapreduce.Job:  map 100% reduce 49%
13/11/26 14:50:42 INFO mapreduce.Job:  map 100% reduce 52%
13/11/26 14:50:45 INFO mapreduce.Job:  map 100% reduce 56%
13/11/26 14:50:48 INFO mapreduce.Job:  map 100% reduce 60%
13/11/26 14:50:51 INFO mapreduce.Job:  map 100% reduce 63%
13/11/26 14:50:53 INFO mapreduce.Job:  map 100% reduce 64%
13/11/26 14:50:54 INFO mapreduce.Job:  map 100% reduce 65%
13/11/26 14:50:57 INFO mapreduce.Job:  map 100% reduce 66%
13/11/26 14:50:58 INFO mapreduce.Job:  map 100% reduce 67%
13/11/26 14:51:04 INFO mapreduce.Job:  map 100% reduce 68%
13/11/26 14:51:07 INFO mapreduce.Job:  map 100% reduce 71%
13/11/26 14:51:10 INFO mapreduce.Job:  map 100% reduce 74%
13/11/26 14:51:13 INFO mapreduce.Job:  map 100% reduce 76%
13/11/26 14:51:16 INFO mapreduce.Job:  map 100% reduce 77%
13/11/26 14:51:25 INFO mapreduce.Job:  map 100% reduce 78%
13/11/26 14:51:32 INFO mapreduce.Job:  map 100% reduce 79%
13/11/26 14:51:35 INFO mapreduce.Job:  map 100% reduce 80%
13/11/26 14:51:43 INFO mapreduce.Job:  map 100% reduce 81%
13/11/26 14:51:50 INFO mapreduce.Job:  map 100% reduce 82%
13/11/26 14:51:59 INFO mapreduce.Job:  map 100% reduce 83%
13/11/26 14:52:11 INFO mapreduce.Job:  map 100% reduce 84%
13/11/26 14:52:21 INFO mapreduce.Job:  map 100% reduce 85%
13/11/26 14:52:30 INFO mapreduce.Job:  map 100% reduce 86%
13/11/26 14:52:40 INFO mapreduce.Job:  map 100% reduce 87%
13/11/26 14:52:50 INFO mapreduce.Job:  map 100% reduce 88%
13/11/26 14:52:59 INFO mapreduce.Job:  map 100% reduce 89%
13/11/26 14:53:05 INFO mapreduce.Job:  map 100% reduce 90%
13/11/26 14:53:14 INFO mapreduce.Job:  map 100% reduce 91%
13/11/26 14:53:23 INFO mapreduce.Job:  map 100% reduce 92%
13/11/26 14:53:33 INFO mapreduce.Job:  map 100% reduce 93%
13/11/26 14:53:42 INFO mapreduce.Job:  map 100% reduce 94%
13/11/26 14:53:48 INFO mapreduce.Job:  map 100% reduce 95%
13/11/26 14:53:57 INFO mapreduce.Job:  map 100% reduce 96%
13/11/26 14:54:06 INFO mapreduce.Job:  map 100% reduce 97%
13/11/26 14:54:16 INFO mapreduce.Job:  map 100% reduce 98%
13/11/26 14:54:28 INFO mapreduce.Job:  map 100% reduce 99%
13/11/26 14:54:40 INFO mapreduce.Job:  map 100% reduce 100%
13/11/26 14:54:45 INFO mapreduce.Job: Job job_1384176415098_0175 completed successfully
13/11/26 14:54:45 INFO mapreduce.Job: Counters: 43
	File System Counters
		FILE: Number of bytes read=11922059372
		FILE: Number of bytes written=17883230228
		FILE: Number of read operations=0
		FILE: Number of large read operations=0
		FILE: Number of write operations=0
		HDFS: Number of bytes read=1813823938
		HDFS: Number of bytes written=3256601520
		HDFS: Number of read operations=120
		HDFS: Number of large read operations=0
		HDFS: Number of write operations=20
	Job Counters 
		Launched map tasks=30
		Launched reduce tasks=10
		Rack-local map tasks=30
		Total time spent by all maps in occupied slots (ms)=3758116
		Total time spent by all reduces in occupied slots (ms)=13009752
	Map-Reduce Framework
		Map input records=5365743
		Map output records=106979944
		Map output bytes=5746061513
		Map output materialized bytes=5960049756
		Input split bytes=3450
		Combine input records=0
		Combine output records=0
		Reduce input groups=13420615
		Reduce shuffle bytes=5960049756
		Reduce input records=106979944
		Reduce output records=13420615
		Spilled Records=320939832
		Shuffled Maps =300
		Failed Shuffles=0
		Merged Map outputs=300
		GC time elapsed (ms)=18279
		CPU time spent (ms)=2401170
		Physical memory (bytes) snapshot=24694779904
		Virtual memory (bytes) snapshot=80618700800
		Total committed heap usage (bytes)=30535843840
	Shuffle Errors
		BAD_ID=0
		CONNECTION=0
		IO_ERROR=0
		WRONG_LENGTH=0
		WRONG_MAP=0
		WRONG_REDUCE=0
	File Input Format Counters 
		Bytes Read=1813820488
	File Output Format Counters 
		Bytes Written=3256601520
13/11/26 14:54:45 INFO streaming.StreamJob: Output directory: /user/huangxuangui/step2/out00
13/11/26 14:54:46 WARN conf.Configuration: mapred.reduce.tasks is deprecated. Instead, use mapreduce.job.reduces
packageJobJar: [/srv/hadoop/hadoop/hadoop-unjar1690916897410623422/] [] /tmp/streamjob1105773297924589998.jar tmpDir=null
13/11/26 14:54:47 INFO service.AbstractService: Service:org.apache.hadoop.yarn.client.YarnClientImpl is inited.
13/11/26 14:54:47 INFO service.AbstractService: Service:org.apache.hadoop.yarn.client.YarnClientImpl is started.
13/11/26 14:54:47 INFO service.AbstractService: Service:org.apache.hadoop.yarn.client.YarnClientImpl is inited.
13/11/26 14:54:47 INFO service.AbstractService: Service:org.apache.hadoop.yarn.client.YarnClientImpl is started.
13/11/26 14:54:47 INFO mapred.FileInputFormat: Total input paths to process : 10
13/11/26 14:54:47 INFO net.NetworkTopology: Adding a new node: /default-rack/192.168.1.150:50010
13/11/26 14:54:47 INFO net.NetworkTopology: Adding a new node: /default-rack/192.168.1.200:50010
13/11/26 14:54:48 INFO mapreduce.JobSubmitter: number of splits:53
13/11/26 14:54:48 WARN conf.Configuration: mapred.jar is deprecated. Instead, use mapreduce.job.jar
13/11/26 14:54:48 WARN conf.Configuration: mapred.cache.files is deprecated. Instead, use mapreduce.job.cache.files
13/11/26 14:54:48 WARN conf.Configuration: mapred.output.value.class is deprecated. Instead, use mapreduce.job.output.value.class
13/11/26 14:54:48 WARN conf.Configuration: mapred.mapoutput.value.class is deprecated. Instead, use mapreduce.map.output.value.class
13/11/26 14:54:48 WARN conf.Configuration: mapred.used.genericoptionsparser is deprecated. Instead, use mapreduce.client.genericoptionsparser.used
13/11/26 14:54:48 WARN conf.Configuration: mapred.job.name is deprecated. Instead, use mapreduce.job.name
13/11/26 14:54:48 WARN conf.Configuration: mapred.input.dir is deprecated. Instead, use mapreduce.input.fileinputformat.inputdir
13/11/26 14:54:48 WARN conf.Configuration: mapred.output.dir is deprecated. Instead, use mapreduce.output.fileoutputformat.outputdir
13/11/26 14:54:48 WARN conf.Configuration: mapred.map.tasks is deprecated. Instead, use mapreduce.job.maps
13/11/26 14:54:48 WARN conf.Configuration: mapred.cache.files.timestamps is deprecated. Instead, use mapreduce.job.cache.files.timestamps
13/11/26 14:54:48 WARN conf.Configuration: mapred.output.key.class is deprecated. Instead, use mapreduce.job.output.key.class
13/11/26 14:54:48 WARN conf.Configuration: mapred.mapoutput.key.class is deprecated. Instead, use mapreduce.map.output.key.class
13/11/26 14:54:48 WARN conf.Configuration: mapred.working.dir is deprecated. Instead, use mapreduce.job.working.dir
13/11/26 14:54:48 INFO mapreduce.JobSubmitter: Submitting tokens for job: job_1384176415098_0176
13/11/26 14:54:48 INFO client.YarnClientImpl: Submitted application application_1384176415098_0176 to ResourceManager at workstation/192.168.1.150:8032
13/11/26 14:54:48 INFO mapreduce.Job: The url to track the job: http://workstation.mshome.net:8043/proxy/application_1384176415098_0176/
13/11/26 14:54:48 INFO mapreduce.Job: Running job: job_1384176415098_0176
13/11/26 14:54:53 INFO mapreduce.Job: Job job_1384176415098_0176 running in uber mode : false
13/11/26 14:54:53 INFO mapreduce.Job:  map 0% reduce 0%
13/11/26 14:55:07 INFO mapreduce.Job:  map 1% reduce 0%
13/11/26 14:55:08 INFO mapreduce.Job:  map 10% reduce 0%
13/11/26 14:55:09 INFO mapreduce.Job:  map 14% reduce 0%
13/11/26 14:55:11 INFO mapreduce.Job:  map 18% reduce 0%
13/11/26 14:55:12 INFO mapreduce.Job:  map 20% reduce 0%
13/11/26 14:55:13 INFO mapreduce.Job:  map 21% reduce 0%
13/11/26 14:55:14 INFO mapreduce.Job:  map 22% reduce 0%
13/11/26 14:55:15 INFO mapreduce.Job:  map 23% reduce 0%
13/11/26 14:55:20 INFO mapreduce.Job:  map 26% reduce 0%
13/11/26 14:55:21 INFO mapreduce.Job:  map 27% reduce 0%
13/11/26 14:55:24 INFO mapreduce.Job:  map 30% reduce 0%
13/11/26 14:55:27 INFO mapreduce.Job:  map 32% reduce 0%
13/11/26 14:55:30 INFO mapreduce.Job:  map 35% reduce 0%
13/11/26 14:55:33 INFO mapreduce.Job:  map 37% reduce 0%
13/11/26 14:55:34 INFO mapreduce.Job:  map 40% reduce 0%
13/11/26 14:55:35 INFO mapreduce.Job:  map 41% reduce 0%
13/11/26 14:55:37 INFO mapreduce.Job:  map 44% reduce 0%
13/11/26 14:55:38 INFO mapreduce.Job:  map 45% reduce 0%
13/11/26 14:55:40 INFO mapreduce.Job:  map 46% reduce 0%
13/11/26 14:55:43 INFO mapreduce.Job:  map 47% reduce 0%
13/11/26 14:55:44 INFO mapreduce.Job:  map 49% reduce 1%
13/11/26 14:55:45 INFO mapreduce.Job:  map 50% reduce 1%
13/11/26 14:55:47 INFO mapreduce.Job:  map 52% reduce 2%
13/11/26 14:55:48 INFO mapreduce.Job:  map 53% reduce 2%
13/11/26 14:55:49 INFO mapreduce.Job:  map 57% reduce 3%
13/11/26 14:55:50 INFO mapreduce.Job:  map 58% reduce 4%
13/11/26 14:55:52 INFO mapreduce.Job:  map 59% reduce 4%
13/11/26 14:55:53 INFO mapreduce.Job:  map 60% reduce 4%
13/11/26 14:55:54 INFO mapreduce.Job:  map 60% reduce 5%
13/11/26 14:55:55 INFO mapreduce.Job:  map 61% reduce 5%
13/11/26 14:55:56 INFO mapreduce.Job:  map 62% reduce 5%
13/11/26 14:55:57 INFO mapreduce.Job:  map 63% reduce 6%
13/11/26 14:55:58 INFO mapreduce.Job:  map 65% reduce 6%
13/11/26 14:55:59 INFO mapreduce.Job:  map 66% reduce 6%
13/11/26 14:56:02 INFO mapreduce.Job:  map 68% reduce 7%
13/11/26 14:56:05 INFO mapreduce.Job:  map 70% reduce 8%
13/11/26 14:56:07 INFO mapreduce.Job:  map 71% reduce 8%
13/11/26 14:56:08 INFO mapreduce.Job:  map 72% reduce 9%
13/11/26 14:56:09 INFO mapreduce.Job:  map 73% reduce 10%
13/11/26 14:56:11 INFO mapreduce.Job:  map 76% reduce 11%
13/11/26 14:56:13 INFO mapreduce.Job:  map 76% reduce 13%
13/11/26 14:56:14 INFO mapreduce.Job:  map 78% reduce 13%
13/11/26 14:56:17 INFO mapreduce.Job:  map 79% reduce 13%
13/11/26 14:56:18 INFO mapreduce.Job:  map 81% reduce 14%
13/11/26 14:56:19 INFO mapreduce.Job:  map 82% reduce 14%
13/11/26 14:56:20 INFO mapreduce.Job:  map 88% reduce 14%
13/11/26 14:56:21 INFO mapreduce.Job:  map 89% reduce 14%
13/11/26 14:56:23 INFO mapreduce.Job:  map 90% reduce 15%
13/11/26 14:56:25 INFO mapreduce.Job:  map 90% reduce 16%
13/11/26 14:56:26 INFO mapreduce.Job:  map 92% reduce 16%
13/11/26 14:56:27 INFO mapreduce.Job:  map 94% reduce 16%
13/11/26 14:56:28 INFO mapreduce.Job:  map 97% reduce 16%
13/11/26 14:56:29 INFO mapreduce.Job:  map 99% reduce 17%
13/11/26 14:56:30 INFO mapreduce.Job:  map 99% reduce 18%
13/11/26 14:56:31 INFO mapreduce.Job:  map 100% reduce 18%
13/11/26 14:56:33 INFO mapreduce.Job:  map 100% reduce 19%
13/11/26 14:56:35 INFO mapreduce.Job:  map 100% reduce 21%
13/11/26 14:56:36 INFO mapreduce.Job:  map 100% reduce 23%
13/11/26 14:56:37 INFO mapreduce.Job:  map 100% reduce 24%
13/11/26 14:56:38 INFO mapreduce.Job:  map 100% reduce 25%
13/11/26 14:56:39 INFO mapreduce.Job:  map 100% reduce 26%
13/11/26 14:56:41 INFO mapreduce.Job:  map 100% reduce 27%
13/11/26 14:56:42 INFO mapreduce.Job:  map 100% reduce 28%
13/11/26 14:56:45 INFO mapreduce.Job:  map 100% reduce 31%
13/11/26 14:56:48 INFO mapreduce.Job:  map 100% reduce 33%
13/11/26 14:56:55 INFO mapreduce.Job:  map 100% reduce 34%
13/11/26 14:56:58 INFO mapreduce.Job:  map 100% reduce 35%
13/11/26 14:57:05 INFO mapreduce.Job:  map 100% reduce 36%
13/11/26 14:57:09 INFO mapreduce.Job:  map 100% reduce 37%
13/11/26 14:57:12 INFO mapreduce.Job:  map 100% reduce 39%
13/11/26 14:57:14 INFO mapreduce.Job:  map 100% reduce 40%
13/11/26 14:57:15 INFO mapreduce.Job:  map 100% reduce 41%
13/11/26 14:57:17 INFO mapreduce.Job:  map 100% reduce 43%
13/11/26 14:57:20 INFO mapreduce.Job:  map 100% reduce 46%
13/11/26 14:57:23 INFO mapreduce.Job:  map 100% reduce 48%
13/11/26 14:57:26 INFO mapreduce.Job:  map 100% reduce 51%
13/11/26 14:57:29 INFO mapreduce.Job:  map 100% reduce 53%
13/11/26 14:57:32 INFO mapreduce.Job:  map 100% reduce 54%
13/11/26 14:57:36 INFO mapreduce.Job:  map 100% reduce 55%
13/11/26 14:57:44 INFO mapreduce.Job:  map 100% reduce 56%
13/11/26 14:57:48 INFO mapreduce.Job:  map 100% reduce 58%
13/11/26 14:57:51 INFO mapreduce.Job:  map 100% reduce 59%
13/11/26 14:57:53 INFO mapreduce.Job:  map 100% reduce 60%
13/11/26 14:57:54 INFO mapreduce.Job:  map 100% reduce 61%
13/11/26 14:57:57 INFO mapreduce.Job:  map 100% reduce 62%
13/11/26 14:57:58 INFO mapreduce.Job:  map 100% reduce 63%
13/11/26 14:58:01 INFO mapreduce.Job:  map 100% reduce 65%
13/11/26 14:58:04 INFO mapreduce.Job:  map 100% reduce 66%
13/11/26 14:58:05 INFO mapreduce.Job:  map 100% reduce 67%
13/11/26 14:58:08 INFO mapreduce.Job:  map 100% reduce 68%
13/11/26 14:58:10 INFO mapreduce.Job:  map 100% reduce 69%
13/11/26 14:58:13 INFO mapreduce.Job:  map 100% reduce 71%
13/11/26 14:58:16 INFO mapreduce.Job:  map 100% reduce 73%
13/11/26 14:58:19 INFO mapreduce.Job:  map 100% reduce 74%
13/11/26 14:58:22 INFO mapreduce.Job:  map 100% reduce 75%
13/11/26 14:58:25 INFO mapreduce.Job:  map 100% reduce 76%
13/11/26 14:58:28 INFO mapreduce.Job:  map 100% reduce 77%
13/11/26 14:58:31 INFO mapreduce.Job:  map 100% reduce 78%
13/11/26 14:58:32 INFO mapreduce.Job:  map 100% reduce 79%
13/11/26 14:58:34 INFO mapreduce.Job:  map 100% reduce 81%
13/11/26 14:58:37 INFO mapreduce.Job:  map 100% reduce 82%
13/11/26 14:58:38 INFO mapreduce.Job:  map 100% reduce 83%
13/11/26 14:58:41 INFO mapreduce.Job:  map 100% reduce 84%
13/11/26 14:58:44 INFO mapreduce.Job:  map 100% reduce 85%
13/11/26 14:58:47 INFO mapreduce.Job:  map 100% reduce 86%
13/11/26 14:58:50 INFO mapreduce.Job:  map 100% reduce 87%
13/11/26 14:58:53 INFO mapreduce.Job:  map 100% reduce 88%
13/11/26 14:58:57 INFO mapreduce.Job:  map 100% reduce 89%
13/11/26 14:59:02 INFO mapreduce.Job:  map 100% reduce 90%
13/11/26 14:59:05 INFO mapreduce.Job:  map 100% reduce 91%
13/11/26 14:59:09 INFO mapreduce.Job:  map 100% reduce 92%
13/11/26 14:59:14 INFO mapreduce.Job:  map 100% reduce 93%
13/11/26 14:59:15 INFO mapreduce.Job:  map 100% reduce 94%
13/11/26 14:59:20 INFO mapreduce.Job:  map 100% reduce 95%
13/11/26 14:59:26 INFO mapreduce.Job:  map 100% reduce 96%
13/11/26 14:59:30 INFO mapreduce.Job:  map 100% reduce 97%
13/11/26 14:59:35 INFO mapreduce.Job:  map 100% reduce 98%
13/11/26 14:59:41 INFO mapreduce.Job:  map 100% reduce 99%
13/11/26 14:59:47 INFO mapreduce.Job:  map 100% reduce 100%
13/11/26 14:59:48 INFO mapreduce.Job: Job job_1384176415098_0176 completed successfully
13/11/26 14:59:48 INFO mapreduce.Job: Counters: 43
	File System Counters
		FILE: Number of bytes read=9923120722
		FILE: Number of bytes written=14994430919
		FILE: Number of read operations=0
		FILE: Number of large read operations=0
		FILE: Number of write operations=0
		HDFS: Number of bytes read=3314701289
		HDFS: Number of bytes written=2078511786
		HDFS: Number of read operations=189
		HDFS: Number of large read operations=0
		HDFS: Number of write operations=20
	Job Counters 
		Launched map tasks=53
		Launched reduce tasks=10
		Rack-local map tasks=53
		Total time spent by all maps in occupied slots (ms)=3132060
		Total time spent by all reduces in occupied slots (ms)=6131904
	Map-Reduce Framework
		Map input records=13420615
		Map output records=115034816
		Map output bytes=4838057958
		Map output materialized bytes=5068157698
		Input split bytes=6201
		Combine input records=0
		Combine output records=0
		Reduce input groups=13420615
		Reduce shuffle bytes=5068157698
		Reduce input records=115034816
		Reduce output records=13420615
		Spilled Records=339491881
		Shuffled Maps =530
		Failed Shuffles=0
		Merged Map outputs=530
		GC time elapsed (ms)=15548
		CPU time spent (ms)=1929830
		Physical memory (bytes) snapshot=29809500160
		Virtual memory (bytes) snapshot=117311766528
		Total committed heap usage (bytes)=36377591808
	Shuffle Errors
		BAD_ID=0
		CONNECTION=0
		IO_ERROR=0
		WRONG_LENGTH=0
		WRONG_MAP=0
		WRONG_REDUCE=0
	File Input Format Counters 
		Bytes Read=3314695088
	File Output Format Counters 
		Bytes Written=2078511786
13/11/26 14:59:48 INFO streaming.StreamJob: Output directory: /user/huangxuangui/step2/out01
13/11/26 14:59:49 WARN conf.Configuration: mapred.reduce.tasks is deprecated. Instead, use mapreduce.job.reduces
packageJobJar: [/srv/hadoop/hadoop/hadoop-unjar5253793794274797855/] [] /tmp/streamjob7543340884469752114.jar tmpDir=null
13/11/26 14:59:50 INFO service.AbstractService: Service:org.apache.hadoop.yarn.client.YarnClientImpl is inited.
13/11/26 14:59:50 INFO service.AbstractService: Service:org.apache.hadoop.yarn.client.YarnClientImpl is started.
13/11/26 14:59:50 INFO service.AbstractService: Service:org.apache.hadoop.yarn.client.YarnClientImpl is inited.
13/11/26 14:59:50 INFO service.AbstractService: Service:org.apache.hadoop.yarn.client.YarnClientImpl is started.
13/11/26 14:59:51 INFO mapred.FileInputFormat: Total input paths to process : 10
13/11/26 14:59:51 INFO net.NetworkTopology: Adding a new node: /default-rack/192.168.1.150:50010
13/11/26 14:59:51 INFO net.NetworkTopology: Adding a new node: /default-rack/192.168.1.200:50010
13/11/26 14:59:51 INFO mapreduce.JobSubmitter: number of splits:33
13/11/26 14:59:51 WARN conf.Configuration: mapred.jar is deprecated. Instead, use mapreduce.job.jar
13/11/26 14:59:51 WARN conf.Configuration: mapred.cache.files is deprecated. Instead, use mapreduce.job.cache.files
13/11/26 14:59:51 WARN conf.Configuration: mapred.output.value.class is deprecated. Instead, use mapreduce.job.output.value.class
13/11/26 14:59:51 WARN conf.Configuration: mapred.mapoutput.value.class is deprecated. Instead, use mapreduce.map.output.value.class
13/11/26 14:59:51 WARN conf.Configuration: mapred.used.genericoptionsparser is deprecated. Instead, use mapreduce.client.genericoptionsparser.used
13/11/26 14:59:51 WARN conf.Configuration: mapred.job.name is deprecated. Instead, use mapreduce.job.name
13/11/26 14:59:51 WARN conf.Configuration: mapred.input.dir is deprecated. Instead, use mapreduce.input.fileinputformat.inputdir
13/11/26 14:59:51 WARN conf.Configuration: mapred.output.dir is deprecated. Instead, use mapreduce.output.fileoutputformat.outputdir
13/11/26 14:59:51 WARN conf.Configuration: mapred.map.tasks is deprecated. Instead, use mapreduce.job.maps
13/11/26 14:59:51 WARN conf.Configuration: mapred.cache.files.timestamps is deprecated. Instead, use mapreduce.job.cache.files.timestamps
13/11/26 14:59:51 WARN conf.Configuration: mapred.output.key.class is deprecated. Instead, use mapreduce.job.output.key.class
13/11/26 14:59:51 WARN conf.Configuration: mapred.mapoutput.key.class is deprecated. Instead, use mapreduce.map.output.key.class
13/11/26 14:59:51 WARN conf.Configuration: mapred.working.dir is deprecated. Instead, use mapreduce.job.working.dir
13/11/26 14:59:51 INFO mapreduce.JobSubmitter: Submitting tokens for job: job_1384176415098_0178
13/11/26 14:59:51 INFO client.YarnClientImpl: Submitted application application_1384176415098_0178 to ResourceManager at workstation/192.168.1.150:8032
13/11/26 14:59:51 INFO mapreduce.Job: The url to track the job: http://workstation.mshome.net:8043/proxy/application_1384176415098_0178/
13/11/26 14:59:51 INFO mapreduce.Job: Running job: job_1384176415098_0178
13/11/26 14:59:57 INFO mapreduce.Job: Job job_1384176415098_0178 running in uber mode : false
13/11/26 14:59:57 INFO mapreduce.Job:  map 0% reduce 0%
13/11/26 15:00:10 INFO mapreduce.Job:  map 2% reduce 0%
13/11/26 15:00:11 INFO mapreduce.Job:  map 7% reduce 0%
13/11/26 15:00:13 INFO mapreduce.Job:  map 8% reduce 0%
13/11/26 15:00:14 INFO mapreduce.Job:  map 12% reduce 0%
13/11/26 15:00:16 INFO mapreduce.Job:  map 13% reduce 0%
13/11/26 15:00:17 INFO mapreduce.Job:  map 16% reduce 0%
13/11/26 15:00:18 INFO mapreduce.Job:  map 17% reduce 0%
13/11/26 15:00:20 INFO mapreduce.Job:  map 19% reduce 0%
13/11/26 15:00:21 INFO mapreduce.Job:  map 20% reduce 0%
13/11/26 15:00:25 INFO mapreduce.Job:  map 21% reduce 0%
13/11/26 15:00:27 INFO mapreduce.Job:  map 23% reduce 0%
13/11/26 15:00:29 INFO mapreduce.Job:  map 25% reduce 0%
13/11/26 15:00:30 INFO mapreduce.Job:  map 27% reduce 0%
13/11/26 15:00:31 INFO mapreduce.Job:  map 28% reduce 0%
13/11/26 15:00:32 INFO mapreduce.Job:  map 30% reduce 0%
13/11/26 15:00:33 INFO mapreduce.Job:  map 31% reduce 0%
13/11/26 15:00:34 INFO mapreduce.Job:  map 32% reduce 0%
13/11/26 15:00:35 INFO mapreduce.Job:  map 34% reduce 0%
13/11/26 15:00:37 INFO mapreduce.Job:  map 35% reduce 0%
13/11/26 15:00:38 INFO mapreduce.Job:  map 36% reduce 0%
13/11/26 15:00:41 INFO mapreduce.Job:  map 38% reduce 0%
13/11/26 15:00:43 INFO mapreduce.Job:  map 40% reduce 0%
13/11/26 15:00:44 INFO mapreduce.Job:  map 42% reduce 0%
13/11/26 15:00:46 INFO mapreduce.Job:  map 43% reduce 0%
13/11/26 15:00:47 INFO mapreduce.Job:  map 45% reduce 0%
13/11/26 15:00:50 INFO mapreduce.Job:  map 46% reduce 0%
13/11/26 15:00:51 INFO mapreduce.Job:  map 47% reduce 0%
13/11/26 15:00:52 INFO mapreduce.Job:  map 48% reduce 0%
13/11/26 15:00:53 INFO mapreduce.Job:  map 49% reduce 0%
13/11/26 15:00:54 INFO mapreduce.Job:  map 50% reduce 0%
13/11/26 15:00:55 INFO mapreduce.Job:  map 52% reduce 0%
13/11/26 15:00:56 INFO mapreduce.Job:  map 54% reduce 0%
13/11/26 15:00:57 INFO mapreduce.Job:  map 56% reduce 0%
13/11/26 15:00:59 INFO mapreduce.Job:  map 58% reduce 0%
13/11/26 15:01:00 INFO mapreduce.Job:  map 60% reduce 0%
13/11/26 15:01:01 INFO mapreduce.Job:  map 62% reduce 0%
13/11/26 15:01:02 INFO mapreduce.Job:  map 64% reduce 0%
13/11/26 15:01:03 INFO mapreduce.Job:  map 65% reduce 0%
13/11/26 15:01:04 INFO mapreduce.Job:  map 66% reduce 0%
13/11/26 15:01:06 INFO mapreduce.Job:  map 67% reduce 0%
13/11/26 15:01:09 INFO mapreduce.Job:  map 68% reduce 0%
13/11/26 15:01:11 INFO mapreduce.Job:  map 69% reduce 0%
13/11/26 15:01:12 INFO mapreduce.Job:  map 71% reduce 0%
13/11/26 15:01:13 INFO mapreduce.Job:  map 71% reduce 1%
13/11/26 15:01:15 INFO mapreduce.Job:  map 72% reduce 1%
13/11/26 15:01:18 INFO mapreduce.Job:  map 73% reduce 1%
13/11/26 15:01:19 INFO mapreduce.Job:  map 75% reduce 1%
13/11/26 15:01:20 INFO mapreduce.Job:  map 76% reduce 1%
13/11/26 15:01:21 INFO mapreduce.Job:  map 77% reduce 1%
13/11/26 15:01:22 INFO mapreduce.Job:  map 78% reduce 1%
13/11/26 15:01:25 INFO mapreduce.Job:  map 79% reduce 1%
13/11/26 15:01:27 INFO mapreduce.Job:  map 79% reduce 3%
13/11/26 15:01:28 INFO mapreduce.Job:  map 80% reduce 5%
13/11/26 15:01:29 INFO mapreduce.Job:  map 87% reduce 8%
13/11/26 15:01:30 INFO mapreduce.Job:  map 90% reduce 9%
13/11/26 15:01:32 INFO mapreduce.Job:  map 91% reduce 10%
13/11/26 15:01:33 INFO mapreduce.Job:  map 92% reduce 10%
13/11/26 15:01:34 INFO mapreduce.Job:  map 92% reduce 11%
13/11/26 15:01:35 INFO mapreduce.Job:  map 93% reduce 11%
13/11/26 15:01:37 INFO mapreduce.Job:  map 94% reduce 11%
13/11/26 15:01:38 INFO mapreduce.Job:  map 95% reduce 11%
13/11/26 15:01:39 INFO mapreduce.Job:  map 98% reduce 13%
13/11/26 15:01:40 INFO mapreduce.Job:  map 98% reduce 15%
13/11/26 15:01:42 INFO mapreduce.Job:  map 99% reduce 16%
13/11/26 15:01:43 INFO mapreduce.Job:  map 99% reduce 17%
13/11/26 15:01:46 INFO mapreduce.Job:  map 99% reduce 19%
13/11/26 15:01:51 INFO mapreduce.Job:  map 100% reduce 19%
13/11/26 15:01:53 INFO mapreduce.Job:  map 100% reduce 20%
13/11/26 15:01:57 INFO mapreduce.Job:  map 100% reduce 21%
13/11/26 15:02:06 INFO mapreduce.Job:  map 100% reduce 22%
13/11/26 15:02:14 INFO mapreduce.Job:  map 100% reduce 23%
13/11/26 15:02:19 INFO mapreduce.Job:  map 100% reduce 24%
13/11/26 15:02:22 INFO mapreduce.Job:  map 100% reduce 25%
13/11/26 15:02:26 INFO mapreduce.Job:  map 100% reduce 26%
13/11/26 15:02:29 INFO mapreduce.Job:  map 100% reduce 28%
13/11/26 15:02:31 INFO mapreduce.Job:  map 100% reduce 29%
13/11/26 15:02:38 INFO mapreduce.Job:  map 100% reduce 30%
13/11/26 15:02:39 INFO mapreduce.Job:  map 100% reduce 31%
13/11/26 15:02:42 INFO mapreduce.Job:  map 100% reduce 33%
13/11/26 15:02:46 INFO mapreduce.Job:  map 100% reduce 34%
13/11/26 15:02:49 INFO mapreduce.Job:  map 100% reduce 35%
13/11/26 15:02:51 INFO mapreduce.Job:  map 100% reduce 36%
13/11/26 15:02:52 INFO mapreduce.Job:  map 100% reduce 37%
13/11/26 15:02:53 INFO mapreduce.Job:  map 100% reduce 38%
13/11/26 15:02:56 INFO mapreduce.Job:  map 100% reduce 41%
13/11/26 15:02:58 INFO mapreduce.Job:  map 100% reduce 42%
13/11/26 15:03:05 INFO mapreduce.Job:  map 100% reduce 43%
13/11/26 15:03:17 INFO mapreduce.Job:  map 100% reduce 44%
13/11/26 15:03:26 INFO mapreduce.Job:  map 100% reduce 45%
13/11/26 15:03:41 INFO mapreduce.Job:  map 100% reduce 46%
13/11/26 15:03:54 INFO mapreduce.Job:  map 100% reduce 47%
13/11/26 15:04:08 INFO mapreduce.Job:  map 100% reduce 48%
13/11/26 15:04:20 INFO mapreduce.Job:  map 100% reduce 49%
13/11/26 15:04:33 INFO mapreduce.Job:  map 100% reduce 50%
13/11/26 15:04:36 INFO mapreduce.Job:  map 100% reduce 51%
13/11/26 15:04:40 INFO mapreduce.Job:  map 100% reduce 53%
13/11/26 15:04:42 INFO mapreduce.Job:  map 100% reduce 54%
13/11/26 15:04:55 INFO mapreduce.Job:  map 100% reduce 55%
13/11/26 15:04:57 INFO mapreduce.Job:  map 100% reduce 57%
13/11/26 15:05:01 INFO mapreduce.Job:  map 100% reduce 59%
13/11/26 15:05:03 INFO mapreduce.Job:  map 100% reduce 60%
13/11/26 15:05:06 INFO mapreduce.Job:  map 100% reduce 61%
13/11/26 15:05:07 INFO mapreduce.Job:  map 100% reduce 62%
13/11/26 15:05:10 INFO mapreduce.Job:  map 100% reduce 63%
13/11/26 15:05:13 INFO mapreduce.Job:  map 100% reduce 65%
13/11/26 15:05:15 INFO mapreduce.Job:  map 100% reduce 66%
13/11/26 15:05:20 INFO mapreduce.Job:  map 100% reduce 67%
13/11/26 15:05:22 INFO mapreduce.Job:  map 100% reduce 68%
13/11/26 15:05:26 INFO mapreduce.Job:  map 100% reduce 69%
13/11/26 15:05:29 INFO mapreduce.Job:  map 100% reduce 70%
13/11/26 15:05:30 INFO mapreduce.Job:  map 100% reduce 71%
13/11/26 15:05:31 INFO mapreduce.Job:  map 100% reduce 73%
13/11/26 15:05:32 INFO mapreduce.Job:  map 100% reduce 74%
13/11/26 15:05:35 INFO mapreduce.Job:  map 100% reduce 75%
13/11/26 15:05:36 INFO mapreduce.Job:  map 100% reduce 76%
13/11/26 15:05:38 INFO mapreduce.Job:  map 100% reduce 77%
13/11/26 15:05:39 INFO mapreduce.Job:  map 100% reduce 78%
13/11/26 15:05:40 INFO mapreduce.Job:  map 100% reduce 79%
13/11/26 15:05:46 INFO mapreduce.Job:  map 100% reduce 80%
13/11/26 15:05:50 INFO mapreduce.Job:  map 100% reduce 81%
13/11/26 15:05:56 INFO mapreduce.Job:  map 100% reduce 82%
13/11/26 15:06:01 INFO mapreduce.Job:  map 100% reduce 83%
13/11/26 15:06:06 INFO mapreduce.Job:  map 100% reduce 84%
13/11/26 15:06:11 INFO mapreduce.Job:  map 100% reduce 85%
13/11/26 15:06:16 INFO mapreduce.Job:  map 100% reduce 86%
13/11/26 15:06:21 INFO mapreduce.Job:  map 100% reduce 87%
13/11/26 15:06:28 INFO mapreduce.Job:  map 100% reduce 88%
13/11/26 15:06:36 INFO mapreduce.Job:  map 100% reduce 89%
13/11/26 15:06:42 INFO mapreduce.Job:  map 100% reduce 90%
13/11/26 15:06:52 INFO mapreduce.Job:  map 100% reduce 91%
13/11/26 15:07:00 INFO mapreduce.Job:  map 100% reduce 92%
13/11/26 15:07:08 INFO mapreduce.Job:  map 100% reduce 93%
13/11/26 15:07:17 INFO mapreduce.Job:  map 100% reduce 94%
13/11/26 15:07:25 INFO mapreduce.Job:  map 100% reduce 95%
13/11/26 15:07:35 INFO mapreduce.Job:  map 100% reduce 96%
13/11/26 15:07:46 INFO mapreduce.Job:  map 100% reduce 97%
13/11/26 15:07:57 INFO mapreduce.Job:  map 100% reduce 98%
13/11/26 15:08:06 INFO mapreduce.Job:  map 100% reduce 99%
13/11/26 15:08:18 INFO mapreduce.Job:  map 100% reduce 100%
13/11/26 15:08:24 INFO mapreduce.Job: Job job_1384176415098_0178 completed successfully
13/11/26 15:08:24 INFO mapreduce.Job: Counters: 43
	File System Counters
		FILE: Number of bytes read=12390897341
		FILE: Number of bytes written=18615095045
		FILE: Number of read operations=0
		FILE: Number of large read operations=0
		FILE: Number of write operations=0
		HDFS: Number of bytes read=2078814655
		HDFS: Number of bytes written=3256612207
		HDFS: Number of read operations=129
		HDFS: Number of large read operations=0
		HDFS: Number of write operations=20
	Job Counters 
		Launched map tasks=33
		Launched reduce tasks=10
		Rack-local map tasks=33
		Total time spent by all maps in occupied slots (ms)=3865766
		Total time spent by all reduces in occupied slots (ms)=11199141
	Map-Reduce Framework
		Map input records=13420615
		Map output records=115034816
		Map output bytes=5992631874
		Map output materialized bytes=6222735799
		Input split bytes=3861
		Combine input records=0
		Combine output records=0
		Reduce input groups=13420615
		Reduce shuffle bytes=6222735799
		Reduce input records=115034816
		Reduce output records=13420615
		Spilled Records=343953277
		Shuffled Maps =330
		Failed Shuffles=0
		Merged Map outputs=330
		GC time elapsed (ms)=20572
		CPU time spent (ms)=2535620
		Physical memory (bytes) snapshot=27535114240
		Virtual memory (bytes) snapshot=85338173440
		Total committed heap usage (bytes)=33017233408
	Shuffle Errors
		BAD_ID=0
		CONNECTION=0
		IO_ERROR=0
		WRONG_LENGTH=0
		WRONG_MAP=0
		WRONG_REDUCE=0
	File Input Format Counters 
		Bytes Read=2078810794
	File Output Format Counters 
		Bytes Written=3256612207
13/11/26 15:08:24 INFO streaming.StreamJob: Output directory: /user/huangxuangui/step2/out10
13/11/26 15:08:25 WARN conf.Configuration: mapred.reduce.tasks is deprecated. Instead, use mapreduce.job.reduces
packageJobJar: [/srv/hadoop/hadoop/hadoop-unjar941587200111625064/] [] /tmp/streamjob8022024048103537482.jar tmpDir=null
13/11/26 15:08:26 INFO service.AbstractService: Service:org.apache.hadoop.yarn.client.YarnClientImpl is inited.
13/11/26 15:08:26 INFO service.AbstractService: Service:org.apache.hadoop.yarn.client.YarnClientImpl is started.
13/11/26 15:08:26 INFO service.AbstractService: Service:org.apache.hadoop.yarn.client.YarnClientImpl is inited.
13/11/26 15:08:26 INFO service.AbstractService: Service:org.apache.hadoop.yarn.client.YarnClientImpl is started.
13/11/26 15:08:27 INFO mapred.FileInputFormat: Total input paths to process : 10
13/11/26 15:08:27 INFO net.NetworkTopology: Adding a new node: /default-rack/192.168.1.150:50010
13/11/26 15:08:27 INFO net.NetworkTopology: Adding a new node: /default-rack/192.168.1.200:50010
13/11/26 15:08:27 INFO mapreduce.JobSubmitter: number of splits:53
13/11/26 15:08:27 WARN conf.Configuration: mapred.jar is deprecated. Instead, use mapreduce.job.jar
13/11/26 15:08:27 WARN conf.Configuration: mapred.cache.files is deprecated. Instead, use mapreduce.job.cache.files
13/11/26 15:08:27 WARN conf.Configuration: mapred.output.value.class is deprecated. Instead, use mapreduce.job.output.value.class
13/11/26 15:08:27 WARN conf.Configuration: mapred.mapoutput.value.class is deprecated. Instead, use mapreduce.map.output.value.class
13/11/26 15:08:27 WARN conf.Configuration: mapred.used.genericoptionsparser is deprecated. Instead, use mapreduce.client.genericoptionsparser.used
13/11/26 15:08:27 WARN conf.Configuration: mapred.job.name is deprecated. Instead, use mapreduce.job.name
13/11/26 15:08:27 WARN conf.Configuration: mapred.input.dir is deprecated. Instead, use mapreduce.input.fileinputformat.inputdir
13/11/26 15:08:27 WARN conf.Configuration: mapred.output.dir is deprecated. Instead, use mapreduce.output.fileoutputformat.outputdir
13/11/26 15:08:27 WARN conf.Configuration: mapred.map.tasks is deprecated. Instead, use mapreduce.job.maps
13/11/26 15:08:27 WARN conf.Configuration: mapred.cache.files.timestamps is deprecated. Instead, use mapreduce.job.cache.files.timestamps
13/11/26 15:08:27 WARN conf.Configuration: mapred.output.key.class is deprecated. Instead, use mapreduce.job.output.key.class
13/11/26 15:08:27 WARN conf.Configuration: mapred.mapoutput.key.class is deprecated. Instead, use mapreduce.map.output.key.class
13/11/26 15:08:27 WARN conf.Configuration: mapred.working.dir is deprecated. Instead, use mapreduce.job.working.dir
13/11/26 15:08:27 INFO mapreduce.JobSubmitter: Submitting tokens for job: job_1384176415098_0179
13/11/26 15:08:27 INFO client.YarnClientImpl: Submitted application application_1384176415098_0179 to ResourceManager at workstation/192.168.1.150:8032
13/11/26 15:08:27 INFO mapreduce.Job: The url to track the job: http://workstation.mshome.net:8043/proxy/application_1384176415098_0179/
13/11/26 15:08:27 INFO mapreduce.Job: Running job: job_1384176415098_0179
13/11/26 15:08:33 INFO mapreduce.Job: Job job_1384176415098_0179 running in uber mode : false
13/11/26 15:08:33 INFO mapreduce.Job:  map 0% reduce 0%
13/11/26 15:08:46 INFO mapreduce.Job:  map 6% reduce 0%
13/11/26 15:08:47 INFO mapreduce.Job:  map 14% reduce 0%
13/11/26 15:08:49 INFO mapreduce.Job:  map 16% reduce 0%
13/11/26 15:08:50 INFO mapreduce.Job:  map 20% reduce 0%
13/11/26 15:08:51 INFO mapreduce.Job:  map 21% reduce 0%
13/11/26 15:08:52 INFO mapreduce.Job:  map 22% reduce 0%
13/11/26 15:08:53 INFO mapreduce.Job:  map 23% reduce 0%
13/11/26 15:08:58 INFO mapreduce.Job:  map 24% reduce 0%
13/11/26 15:08:59 INFO mapreduce.Job:  map 25% reduce 0%
13/11/26 15:09:00 INFO mapreduce.Job:  map 27% reduce 0%
13/11/26 15:09:03 INFO mapreduce.Job:  map 29% reduce 0%
13/11/26 15:09:04 INFO mapreduce.Job:  map 31% reduce 0%
13/11/26 15:09:06 INFO mapreduce.Job:  map 32% reduce 0%
13/11/26 15:09:07 INFO mapreduce.Job:  map 33% reduce 0%
13/11/26 15:09:08 INFO mapreduce.Job:  map 34% reduce 0%
13/11/26 15:09:09 INFO mapreduce.Job:  map 38% reduce 0%
13/11/26 15:09:10 INFO mapreduce.Job:  map 41% reduce 0%
13/11/26 15:09:13 INFO mapreduce.Job:  map 44% reduce 0%
13/11/26 15:09:16 INFO mapreduce.Job:  map 45% reduce 0%
13/11/26 15:09:17 INFO mapreduce.Job:  map 46% reduce 0%
13/11/26 15:09:19 INFO mapreduce.Job:  map 48% reduce 0%
13/11/26 15:09:21 INFO mapreduce.Job:  map 50% reduce 0%
13/11/26 15:09:22 INFO mapreduce.Job:  map 52% reduce 0%
13/11/26 15:09:23 INFO mapreduce.Job:  map 52% reduce 1%
13/11/26 15:09:24 INFO mapreduce.Job:  map 54% reduce 1%
13/11/26 15:09:27 INFO mapreduce.Job:  map 54% reduce 3%
13/11/26 15:09:28 INFO mapreduce.Job:  map 55% reduce 4%
13/11/26 15:09:29 INFO mapreduce.Job:  map 55% reduce 6%
13/11/26 15:09:30 INFO mapreduce.Job:  map 56% reduce 6%
13/11/26 15:09:31 INFO mapreduce.Job:  map 58% reduce 6%
13/11/26 15:09:33 INFO mapreduce.Job:  map 61% reduce 6%
13/11/26 15:09:34 INFO mapreduce.Job:  map 62% reduce 6%
13/11/26 15:09:35 INFO mapreduce.Job:  map 63% reduce 7%
13/11/26 15:09:36 INFO mapreduce.Job:  map 64% reduce 7%
13/11/26 15:09:37 INFO mapreduce.Job:  map 65% reduce 7%
13/11/26 15:09:38 INFO mapreduce.Job:  map 67% reduce 8%
13/11/26 15:09:40 INFO mapreduce.Job:  map 69% reduce 8%
13/11/26 15:09:41 INFO mapreduce.Job:  map 70% reduce 9%
13/11/26 15:09:42 INFO mapreduce.Job:  map 71% reduce 9%
13/11/26 15:09:45 INFO mapreduce.Job:  map 71% reduce 10%
13/11/26 15:09:46 INFO mapreduce.Job:  map 73% reduce 10%
13/11/26 15:09:47 INFO mapreduce.Job:  map 74% reduce 11%
13/11/26 15:09:48 INFO mapreduce.Job:  map 76% reduce 12%
13/11/26 15:09:49 INFO mapreduce.Job:  map 77% reduce 12%
13/11/26 15:09:51 INFO mapreduce.Job:  map 79% reduce 12%
13/11/26 15:09:52 INFO mapreduce.Job:  map 80% reduce 12%
13/11/26 15:09:53 INFO mapreduce.Job:  map 80% reduce 13%
13/11/26 15:09:55 INFO mapreduce.Job:  map 81% reduce 13%
13/11/26 15:09:57 INFO mapreduce.Job:  map 82% reduce 14%
13/11/26 15:09:58 INFO mapreduce.Job:  map 88% reduce 14%
13/11/26 15:09:59 INFO mapreduce.Job:  map 89% reduce 14%
13/11/26 15:10:00 INFO mapreduce.Job:  map 91% reduce 14%
13/11/26 15:10:02 INFO mapreduce.Job:  map 92% reduce 14%
13/11/26 15:10:03 INFO mapreduce.Job:  map 94% reduce 16%
13/11/26 15:10:04 INFO mapreduce.Job:  map 98% reduce 16%
13/11/26 15:10:06 INFO mapreduce.Job:  map 100% reduce 17%
13/11/26 15:10:09 INFO mapreduce.Job:  map 100% reduce 18%
13/11/26 15:10:12 INFO mapreduce.Job:  map 100% reduce 20%
13/11/26 15:10:13 INFO mapreduce.Job:  map 100% reduce 24%
13/11/26 15:10:18 INFO mapreduce.Job:  map 100% reduce 25%
13/11/26 15:10:21 INFO mapreduce.Job:  map 100% reduce 26%
13/11/26 15:10:25 INFO mapreduce.Job:  map 100% reduce 28%
13/11/26 15:10:27 INFO mapreduce.Job:  map 100% reduce 30%
13/11/26 15:10:28 INFO mapreduce.Job:  map 100% reduce 31%
13/11/26 15:10:30 INFO mapreduce.Job:  map 100% reduce 32%
13/11/26 15:10:32 INFO mapreduce.Job:  map 100% reduce 33%
13/11/26 15:10:34 INFO mapreduce.Job:  map 100% reduce 34%
13/11/26 15:10:37 INFO mapreduce.Job:  map 100% reduce 35%
13/11/26 15:10:40 INFO mapreduce.Job:  map 100% reduce 36%
13/11/26 15:10:43 INFO mapreduce.Job:  map 100% reduce 38%
13/11/26 15:10:45 INFO mapreduce.Job:  map 100% reduce 39%
13/11/26 15:10:48 INFO mapreduce.Job:  map 100% reduce 40%
13/11/26 15:10:54 INFO mapreduce.Job:  map 100% reduce 41%
13/11/26 15:10:57 INFO mapreduce.Job:  map 100% reduce 42%
13/11/26 15:11:01 INFO mapreduce.Job:  map 100% reduce 43%
13/11/26 15:11:03 INFO mapreduce.Job:  map 100% reduce 44%
13/11/26 15:11:04 INFO mapreduce.Job:  map 100% reduce 45%
13/11/26 15:11:06 INFO mapreduce.Job:  map 100% reduce 46%
13/11/26 15:11:07 INFO mapreduce.Job:  map 100% reduce 47%
13/11/26 15:11:09 INFO mapreduce.Job:  map 100% reduce 49%
13/11/26 15:11:10 INFO mapreduce.Job:  map 100% reduce 50%
13/11/26 15:11:12 INFO mapreduce.Job:  map 100% reduce 52%
13/11/26 15:11:14 INFO mapreduce.Job:  map 100% reduce 53%
13/11/26 15:11:15 INFO mapreduce.Job:  map 100% reduce 54%
13/11/26 15:11:16 INFO mapreduce.Job:  map 100% reduce 56%
13/11/26 15:11:19 INFO mapreduce.Job:  map 100% reduce 57%
13/11/26 15:11:20 INFO mapreduce.Job:  map 100% reduce 58%
13/11/26 15:11:21 INFO mapreduce.Job:  map 100% reduce 59%
13/11/26 15:11:22 INFO mapreduce.Job:  map 100% reduce 60%
13/11/26 15:11:25 INFO mapreduce.Job:  map 100% reduce 61%
13/11/26 15:11:26 INFO mapreduce.Job:  map 100% reduce 62%
13/11/26 15:11:27 INFO mapreduce.Job:  map 100% reduce 63%
13/11/26 15:11:28 INFO mapreduce.Job:  map 100% reduce 64%
13/11/26 15:11:31 INFO mapreduce.Job:  map 100% reduce 65%
13/11/26 15:11:33 INFO mapreduce.Job:  map 100% reduce 66%
13/11/26 15:11:37 INFO mapreduce.Job:  map 100% reduce 68%
13/11/26 15:11:40 INFO mapreduce.Job:  map 100% reduce 69%
13/11/26 15:11:43 INFO mapreduce.Job:  map 100% reduce 70%
13/11/26 15:11:44 INFO mapreduce.Job:  map 100% reduce 71%
13/11/26 15:11:47 INFO mapreduce.Job:  map 100% reduce 72%
13/11/26 15:11:52 INFO mapreduce.Job:  map 100% reduce 73%
13/11/26 15:11:56 INFO mapreduce.Job:  map 100% reduce 74%
13/11/26 15:12:00 INFO mapreduce.Job:  map 100% reduce 75%
13/11/26 15:12:04 INFO mapreduce.Job:  map 100% reduce 76%
13/11/26 15:12:09 INFO mapreduce.Job:  map 100% reduce 77%
13/11/26 15:12:12 INFO mapreduce.Job:  map 100% reduce 78%
13/11/26 15:12:16 INFO mapreduce.Job:  map 100% reduce 79%
13/11/26 15:12:20 INFO mapreduce.Job:  map 100% reduce 80%
13/11/26 15:12:23 INFO mapreduce.Job:  map 100% reduce 81%
13/11/26 15:12:24 INFO mapreduce.Job:  map 100% reduce 82%
13/11/26 15:12:26 INFO mapreduce.Job:  map 100% reduce 83%
13/11/26 15:12:27 INFO mapreduce.Job:  map 100% reduce 84%
13/11/26 15:12:30 INFO mapreduce.Job:  map 100% reduce 85%
13/11/26 15:12:31 INFO mapreduce.Job:  map 100% reduce 86%
13/11/26 15:12:33 INFO mapreduce.Job:  map 100% reduce 87%
13/11/26 15:12:34 INFO mapreduce.Job:  map 100% reduce 88%
13/11/26 15:12:35 INFO mapreduce.Job:  map 100% reduce 89%
13/11/26 15:12:39 INFO mapreduce.Job:  map 100% reduce 90%
13/11/26 15:12:42 INFO mapreduce.Job:  map 100% reduce 91%
13/11/26 15:12:48 INFO mapreduce.Job:  map 100% reduce 92%
13/11/26 15:12:52 INFO mapreduce.Job:  map 100% reduce 93%
13/11/26 15:12:55 INFO mapreduce.Job:  map 100% reduce 94%
13/11/26 15:12:58 INFO mapreduce.Job:  map 100% reduce 95%
13/11/26 15:13:01 INFO mapreduce.Job:  map 100% reduce 96%
13/11/26 15:13:06 INFO mapreduce.Job:  map 100% reduce 97%
13/11/26 15:13:12 INFO mapreduce.Job:  map 100% reduce 98%
13/11/26 15:13:16 INFO mapreduce.Job:  map 100% reduce 99%
13/11/26 15:13:25 INFO mapreduce.Job:  map 100% reduce 100%
13/11/26 15:13:27 INFO mapreduce.Job: Job job_1384176415098_0179 completed successfully
13/11/26 15:13:27 INFO mapreduce.Job: Counters: 44
	File System Counters
		FILE: Number of bytes read=9923214314
		FILE: Number of bytes written=14994488783
		FILE: Number of read operations=0
		FILE: Number of large read operations=0
		FILE: Number of write operations=0
		HDFS: Number of bytes read=3314720168
		HDFS: Number of bytes written=2078522473
		HDFS: Number of read operations=189
		HDFS: Number of large read operations=0
		HDFS: Number of write operations=20
	Job Counters 
		Killed map tasks=1
		Launched map tasks=54
		Launched reduce tasks=10
		Rack-local map tasks=54
		Total time spent by all maps in occupied slots (ms)=2959972
		Total time spent by all reduces in occupied slots (ms)=6230454
	Map-Reduce Framework
		Map input records=13420615
		Map output records=115034816
		Map output bytes=4838079332
		Map output materialized bytes=5068179072
		Input split bytes=6201
		Combine input records=0
		Combine output records=0
		Reduce input groups=13420615
		Reduce shuffle bytes=5068179072
		Reduce input records=115034816
		Reduce output records=13420615
		Spilled Records=339491759
		Shuffled Maps =530
		Failed Shuffles=0
		Merged Map outputs=530
		GC time elapsed (ms)=15744
		CPU time spent (ms)=1881610
		Physical memory (bytes) snapshot=29232791552
		Virtual memory (bytes) snapshot=117233721344
		Total committed heap usage (bytes)=36293246976
	Shuffle Errors
		BAD_ID=0
		CONNECTION=0
		IO_ERROR=0
		WRONG_LENGTH=0
		WRONG_MAP=0
		WRONG_REDUCE=0
	File Input Format Counters 
		Bytes Read=3314713967
	File Output Format Counters 
		Bytes Written=2078522473
13/11/26 15:13:27 INFO streaming.StreamJob: Output directory: /user/huangxuangui/step2/out11
13/11/26 15:13:28 WARN conf.Configuration: mapred.reduce.tasks is deprecated. Instead, use mapreduce.job.reduces
packageJobJar: [/srv/hadoop/hadoop/hadoop-unjar8955883921214503697/] [] /tmp/streamjob2486287895520051973.jar tmpDir=null
13/11/26 15:13:28 INFO service.AbstractService: Service:org.apache.hadoop.yarn.client.YarnClientImpl is inited.
13/11/26 15:13:28 INFO service.AbstractService: Service:org.apache.hadoop.yarn.client.YarnClientImpl is started.
13/11/26 15:13:28 INFO service.AbstractService: Service:org.apache.hadoop.yarn.client.YarnClientImpl is inited.
13/11/26 15:13:28 INFO service.AbstractService: Service:org.apache.hadoop.yarn.client.YarnClientImpl is started.
13/11/26 15:13:29 INFO mapred.FileInputFormat: Total input paths to process : 10
13/11/26 15:13:29 INFO net.NetworkTopology: Adding a new node: /default-rack/192.168.1.150:50010
13/11/26 15:13:29 INFO net.NetworkTopology: Adding a new node: /default-rack/192.168.1.200:50010
13/11/26 15:13:29 INFO mapreduce.JobSubmitter: number of splits:33
13/11/26 15:13:29 WARN conf.Configuration: mapred.jar is deprecated. Instead, use mapreduce.job.jar
13/11/26 15:13:29 WARN conf.Configuration: mapred.cache.files is deprecated. Instead, use mapreduce.job.cache.files
13/11/26 15:13:29 WARN conf.Configuration: mapred.output.value.class is deprecated. Instead, use mapreduce.job.output.value.class
13/11/26 15:13:29 WARN conf.Configuration: mapred.mapoutput.value.class is deprecated. Instead, use mapreduce.map.output.value.class
13/11/26 15:13:29 WARN conf.Configuration: mapred.used.genericoptionsparser is deprecated. Instead, use mapreduce.client.genericoptionsparser.used
13/11/26 15:13:29 WARN conf.Configuration: mapred.job.name is deprecated. Instead, use mapreduce.job.name
13/11/26 15:13:29 WARN conf.Configuration: mapred.input.dir is deprecated. Instead, use mapreduce.input.fileinputformat.inputdir
13/11/26 15:13:29 WARN conf.Configuration: mapred.output.dir is deprecated. Instead, use mapreduce.output.fileoutputformat.outputdir
13/11/26 15:13:29 WARN conf.Configuration: mapred.map.tasks is deprecated. Instead, use mapreduce.job.maps
13/11/26 15:13:29 WARN conf.Configuration: mapred.cache.files.timestamps is deprecated. Instead, use mapreduce.job.cache.files.timestamps
13/11/26 15:13:29 WARN conf.Configuration: mapred.output.key.class is deprecated. Instead, use mapreduce.job.output.key.class
13/11/26 15:13:29 WARN conf.Configuration: mapred.mapoutput.key.class is deprecated. Instead, use mapreduce.map.output.key.class
13/11/26 15:13:29 WARN conf.Configuration: mapred.working.dir is deprecated. Instead, use mapreduce.job.working.dir
13/11/26 15:13:29 INFO mapreduce.JobSubmitter: Submitting tokens for job: job_1384176415098_0181
13/11/26 15:13:30 INFO client.YarnClientImpl: Submitted application application_1384176415098_0181 to ResourceManager at workstation/192.168.1.150:8032
13/11/26 15:13:30 INFO mapreduce.Job: The url to track the job: http://workstation.mshome.net:8043/proxy/application_1384176415098_0181/
13/11/26 15:13:30 INFO mapreduce.Job: Running job: job_1384176415098_0181
13/11/26 15:13:35 INFO mapreduce.Job: Job job_1384176415098_0181 running in uber mode : false
13/11/26 15:13:35 INFO mapreduce.Job:  map 0% reduce 0%
13/11/26 15:13:49 INFO mapreduce.Job:  map 7% reduce 0%
13/11/26 15:13:52 INFO mapreduce.Job:  map 12% reduce 0%
13/11/26 15:13:55 INFO mapreduce.Job:  map 16% reduce 0%
13/11/26 15:13:56 INFO mapreduce.Job:  map 17% reduce 0%
13/11/26 15:13:58 INFO mapreduce.Job:  map 19% reduce 0%
13/11/26 15:13:59 INFO mapreduce.Job:  map 20% reduce 0%
13/11/26 15:14:04 INFO mapreduce.Job:  map 21% reduce 0%
13/11/26 15:14:05 INFO mapreduce.Job:  map 23% reduce 0%
13/11/26 15:14:08 INFO mapreduce.Job:  map 27% reduce 0%
13/11/26 15:14:09 INFO mapreduce.Job:  map 28% reduce 0%
13/11/26 15:14:11 INFO mapreduce.Job:  map 31% reduce 0%
13/11/26 15:14:12 INFO mapreduce.Job:  map 32% reduce 0%
13/11/26 15:14:14 INFO mapreduce.Job:  map 34% reduce 0%
13/11/26 15:14:15 INFO mapreduce.Job:  map 35% reduce 0%
13/11/26 15:14:18 INFO mapreduce.Job:  map 36% reduce 0%
13/11/26 15:14:20 INFO mapreduce.Job:  map 37% reduce 0%
13/11/26 15:14:21 INFO mapreduce.Job:  map 39% reduce 0%
13/11/26 15:14:23 INFO mapreduce.Job:  map 41% reduce 0%
13/11/26 15:14:24 INFO mapreduce.Job:  map 43% reduce 0%
13/11/26 15:14:26 INFO mapreduce.Job:  map 44% reduce 0%
13/11/26 15:14:27 INFO mapreduce.Job:  map 45% reduce 0%
13/11/26 15:14:29 INFO mapreduce.Job:  map 46% reduce 0%
13/11/26 15:14:30 INFO mapreduce.Job:  map 47% reduce 0%
13/11/26 15:14:32 INFO mapreduce.Job:  map 48% reduce 0%
13/11/26 15:14:33 INFO mapreduce.Job:  map 52% reduce 0%
13/11/26 15:14:34 INFO mapreduce.Job:  map 53% reduce 0%
13/11/26 15:14:36 INFO mapreduce.Job:  map 56% reduce 0%
13/11/26 15:14:37 INFO mapreduce.Job:  map 59% reduce 0%
13/11/26 15:14:39 INFO mapreduce.Job:  map 62% reduce 0%
13/11/26 15:14:40 INFO mapreduce.Job:  map 65% reduce 0%
13/11/26 15:14:41 INFO mapreduce.Job:  map 66% reduce 0%
13/11/26 15:14:43 INFO mapreduce.Job:  map 68% reduce 0%
13/11/26 15:14:46 INFO mapreduce.Job:  map 69% reduce 0%
13/11/26 15:14:47 INFO mapreduce.Job:  map 70% reduce 0%
13/11/26 15:14:48 INFO mapreduce.Job:  map 72% reduce 0%
13/11/26 15:14:51 INFO mapreduce.Job:  map 73% reduce 0%
13/11/26 15:14:53 INFO mapreduce.Job:  map 74% reduce 2%
13/11/26 15:14:55 INFO mapreduce.Job:  map 74% reduce 7%
13/11/26 15:14:56 INFO mapreduce.Job:  map 81% reduce 7%
13/11/26 15:14:57 INFO mapreduce.Job:  map 85% reduce 9%
13/11/26 15:15:00 INFO mapreduce.Job:  map 87% reduce 11%
13/11/26 15:15:01 INFO mapreduce.Job:  map 87% reduce 12%
13/11/26 15:15:02 INFO mapreduce.Job:  map 88% reduce 12%
13/11/26 15:15:03 INFO mapreduce.Job:  map 89% reduce 12%
13/11/26 15:15:06 INFO mapreduce.Job:  map 91% reduce 12%
13/11/26 15:15:07 INFO mapreduce.Job:  map 91% reduce 13%
13/11/26 15:15:09 INFO mapreduce.Job:  map 92% reduce 14%
13/11/26 15:15:11 INFO mapreduce.Job:  map 94% reduce 14%
13/11/26 15:15:13 INFO mapreduce.Job:  map 96% reduce 14%
13/11/26 15:15:14 INFO mapreduce.Job:  map 97% reduce 14%
13/11/26 15:15:15 INFO mapreduce.Job:  map 98% reduce 16%
13/11/26 15:15:19 INFO mapreduce.Job:  map 99% reduce 17%
13/11/26 15:15:22 INFO mapreduce.Job:  map 100% reduce 19%
13/11/26 15:15:26 INFO mapreduce.Job:  map 100% reduce 21%
13/11/26 15:15:35 INFO mapreduce.Job:  map 100% reduce 22%
13/11/26 15:15:45 INFO mapreduce.Job:  map 100% reduce 23%
13/11/26 15:15:53 INFO mapreduce.Job:  map 100% reduce 24%
13/11/26 15:16:01 INFO mapreduce.Job:  map 100% reduce 25%
13/11/26 15:16:10 INFO mapreduce.Job:  map 100% reduce 26%
13/11/26 15:16:18 INFO mapreduce.Job:  map 100% reduce 27%
13/11/26 15:16:22 INFO mapreduce.Job:  map 100% reduce 28%
13/11/26 15:16:29 INFO mapreduce.Job:  map 100% reduce 29%
13/11/26 15:16:36 INFO mapreduce.Job:  map 100% reduce 30%
13/11/26 15:16:41 INFO mapreduce.Job:  map 100% reduce 31%
13/11/26 15:16:46 INFO mapreduce.Job:  map 100% reduce 32%
13/11/26 15:16:48 INFO mapreduce.Job:  map 100% reduce 34%
13/11/26 15:16:49 INFO mapreduce.Job:  map 100% reduce 35%
13/11/26 15:16:50 INFO mapreduce.Job:  map 100% reduce 37%
13/11/26 15:16:51 INFO mapreduce.Job:  map 100% reduce 38%
13/11/26 15:16:52 INFO mapreduce.Job:  map 100% reduce 39%
13/11/26 15:16:53 INFO mapreduce.Job:  map 100% reduce 43%
13/11/26 15:16:56 INFO mapreduce.Job:  map 100% reduce 44%
13/11/26 15:16:57 INFO mapreduce.Job:  map 100% reduce 48%
13/11/26 15:16:58 INFO mapreduce.Job:  map 100% reduce 49%
13/11/26 15:16:59 INFO mapreduce.Job:  map 100% reduce 50%
13/11/26 15:17:00 INFO mapreduce.Job:  map 100% reduce 51%
13/11/26 15:17:01 INFO mapreduce.Job:  map 100% reduce 52%
13/11/26 15:17:03 INFO mapreduce.Job:  map 100% reduce 53%
13/11/26 15:17:04 INFO mapreduce.Job:  map 100% reduce 55%
13/11/26 15:17:05 INFO mapreduce.Job:  map 100% reduce 56%
13/11/26 15:17:06 INFO mapreduce.Job:  map 100% reduce 58%
13/11/26 15:17:08 INFO mapreduce.Job:  map 100% reduce 60%
13/11/26 15:17:11 INFO mapreduce.Job:  map 100% reduce 61%
13/11/26 15:17:12 INFO mapreduce.Job:  map 100% reduce 62%
13/11/26 15:17:15 INFO mapreduce.Job:  map 100% reduce 64%
13/11/26 15:17:16 INFO mapreduce.Job:  map 100% reduce 65%
13/11/26 15:17:19 INFO mapreduce.Job:  map 100% reduce 67%
13/11/26 15:17:21 INFO mapreduce.Job:  map 100% reduce 68%
13/11/26 15:17:22 INFO mapreduce.Job:  map 100% reduce 69%
13/11/26 15:17:23 INFO mapreduce.Job:  map 100% reduce 70%
13/11/26 15:17:26 INFO mapreduce.Job:  map 100% reduce 71%
13/11/26 15:17:28 INFO mapreduce.Job:  map 100% reduce 72%
13/11/26 15:17:35 INFO mapreduce.Job:  map 100% reduce 73%
13/11/26 15:17:39 INFO mapreduce.Job:  map 100% reduce 74%
13/11/26 15:17:44 INFO mapreduce.Job:  map 100% reduce 75%
13/11/26 15:17:49 INFO mapreduce.Job:  map 100% reduce 76%
13/11/26 15:17:53 INFO mapreduce.Job:  map 100% reduce 77%
13/11/26 15:17:59 INFO mapreduce.Job:  map 100% reduce 78%
13/11/26 15:18:04 INFO mapreduce.Job:  map 100% reduce 79%
13/11/26 15:18:08 INFO mapreduce.Job:  map 100% reduce 80%
13/11/26 15:18:14 INFO mapreduce.Job:  map 100% reduce 81%
13/11/26 15:18:18 INFO mapreduce.Job:  map 100% reduce 82%
13/11/26 15:18:21 INFO mapreduce.Job:  map 100% reduce 83%
13/11/26 15:18:26 INFO mapreduce.Job:  map 100% reduce 84%
13/11/26 15:18:29 INFO mapreduce.Job:  map 100% reduce 85%
13/11/26 15:18:35 INFO mapreduce.Job:  map 100% reduce 86%
13/11/26 15:18:39 INFO mapreduce.Job:  map 100% reduce 87%
13/11/26 15:18:45 INFO mapreduce.Job:  map 100% reduce 88%
13/11/26 15:18:48 INFO mapreduce.Job:  map 100% reduce 89%
13/11/26 15:18:53 INFO mapreduce.Job:  map 100% reduce 90%
13/11/26 15:18:57 INFO mapreduce.Job:  map 100% reduce 91%
13/11/26 15:19:02 INFO mapreduce.Job:  map 100% reduce 92%
13/11/26 15:19:07 INFO mapreduce.Job:  map 100% reduce 93%
13/11/26 15:19:10 INFO mapreduce.Job:  map 100% reduce 94%
13/11/26 15:19:16 INFO mapreduce.Job:  map 100% reduce 95%
13/11/26 15:19:20 INFO mapreduce.Job:  map 100% reduce 96%
13/11/26 15:19:25 INFO mapreduce.Job:  map 100% reduce 97%
13/11/26 15:19:30 INFO mapreduce.Job:  map 100% reduce 98%
13/11/26 15:19:37 INFO mapreduce.Job:  map 100% reduce 99%
13/11/26 15:19:44 INFO mapreduce.Job:  map 100% reduce 100%
13/11/26 15:19:48 INFO mapreduce.Job: Job job_1384176415098_0181 completed successfully
13/11/26 15:19:48 INFO mapreduce.Job: Counters: 43
	File System Counters
		FILE: Number of bytes read=12394496752
		FILE: Number of bytes written=18620490219
		FILE: Number of read operations=0
		FILE: Number of large read operations=0
		FILE: Number of write operations=0
		HDFS: Number of bytes read=2078825342
		HDFS: Number of bytes written=3256619548
		HDFS: Number of read operations=129
		HDFS: Number of large read operations=0
		HDFS: Number of write operations=20
	Job Counters 
		Launched map tasks=33
		Launched reduce tasks=10
		Rack-local map tasks=33
		Total time spent by all maps in occupied slots (ms)=3599162
		Total time spent by all reduces in occupied slots (ms)=8530020
	Map-Reduce Framework
		Map input records=13420615
		Map output records=115034816
		Map output bytes=5994434904
		Map output materialized bytes=6224538829
		Input split bytes=3861
		Combine input records=0
		Combine output records=0
		Reduce input groups=13420615
		Reduce shuffle bytes=6224538829
		Reduce input records=115034816
		Reduce output records=13420615
		Spilled Records=343953277
		Shuffled Maps =330
		Failed Shuffles=0
		Merged Map outputs=330
		GC time elapsed (ms)=23188
		CPU time spent (ms)=2566840
		Physical memory (bytes) snapshot=25850998784
		Virtual memory (bytes) snapshot=85369040896
		Total committed heap usage (bytes)=32280543232
	Shuffle Errors
		BAD_ID=0
		CONNECTION=0
		IO_ERROR=0
		WRONG_LENGTH=0
		WRONG_MAP=0
		WRONG_REDUCE=0
	File Input Format Counters 
		Bytes Read=2078821481
	File Output Format Counters 
		Bytes Written=3256619548
13/11/26 15:19:48 INFO streaming.StreamJob: Output directory: /user/huangxuangui/step2/out20
13/11/26 15:19:49 WARN conf.Configuration: mapred.reduce.tasks is deprecated. Instead, use mapreduce.job.reduces
packageJobJar: [/srv/hadoop/hadoop/hadoop-unjar6007342123766435490/] [] /tmp/streamjob4878226150695504785.jar tmpDir=null
13/11/26 15:19:49 INFO service.AbstractService: Service:org.apache.hadoop.yarn.client.YarnClientImpl is inited.
13/11/26 15:19:49 INFO service.AbstractService: Service:org.apache.hadoop.yarn.client.YarnClientImpl is started.
13/11/26 15:19:49 INFO service.AbstractService: Service:org.apache.hadoop.yarn.client.YarnClientImpl is inited.
13/11/26 15:19:49 INFO service.AbstractService: Service:org.apache.hadoop.yarn.client.YarnClientImpl is started.
13/11/26 15:19:50 INFO mapred.FileInputFormat: Total input paths to process : 10
13/11/26 15:19:50 INFO net.NetworkTopology: Adding a new node: /default-rack/192.168.1.150:50010
13/11/26 15:19:50 INFO net.NetworkTopology: Adding a new node: /default-rack/192.168.1.200:50010
13/11/26 15:19:50 INFO mapreduce.JobSubmitter: number of splits:53
13/11/26 15:19:50 WARN conf.Configuration: mapred.jar is deprecated. Instead, use mapreduce.job.jar
13/11/26 15:19:50 WARN conf.Configuration: mapred.cache.files is deprecated. Instead, use mapreduce.job.cache.files
13/11/26 15:19:50 WARN conf.Configuration: mapred.output.value.class is deprecated. Instead, use mapreduce.job.output.value.class
13/11/26 15:19:50 WARN conf.Configuration: mapred.mapoutput.value.class is deprecated. Instead, use mapreduce.map.output.value.class
13/11/26 15:19:50 WARN conf.Configuration: mapred.used.genericoptionsparser is deprecated. Instead, use mapreduce.client.genericoptionsparser.used
13/11/26 15:19:50 WARN conf.Configuration: mapred.job.name is deprecated. Instead, use mapreduce.job.name
13/11/26 15:19:50 WARN conf.Configuration: mapred.input.dir is deprecated. Instead, use mapreduce.input.fileinputformat.inputdir
13/11/26 15:19:50 WARN conf.Configuration: mapred.output.dir is deprecated. Instead, use mapreduce.output.fileoutputformat.outputdir
13/11/26 15:19:50 WARN conf.Configuration: mapred.map.tasks is deprecated. Instead, use mapreduce.job.maps
13/11/26 15:19:50 WARN conf.Configuration: mapred.cache.files.timestamps is deprecated. Instead, use mapreduce.job.cache.files.timestamps
13/11/26 15:19:50 WARN conf.Configuration: mapred.output.key.class is deprecated. Instead, use mapreduce.job.output.key.class
13/11/26 15:19:50 WARN conf.Configuration: mapred.mapoutput.key.class is deprecated. Instead, use mapreduce.map.output.key.class
13/11/26 15:19:50 WARN conf.Configuration: mapred.working.dir is deprecated. Instead, use mapreduce.job.working.dir
13/11/26 15:19:50 INFO mapreduce.JobSubmitter: Submitting tokens for job: job_1384176415098_0183
13/11/26 15:19:50 INFO client.YarnClientImpl: Submitted application application_1384176415098_0183 to ResourceManager at workstation/192.168.1.150:8032
13/11/26 15:19:50 INFO mapreduce.Job: The url to track the job: http://workstation.mshome.net:8043/proxy/application_1384176415098_0183/
13/11/26 15:19:50 INFO mapreduce.Job: Running job: job_1384176415098_0183
13/11/26 15:19:56 INFO mapreduce.Job: Job job_1384176415098_0183 running in uber mode : false
13/11/26 15:19:56 INFO mapreduce.Job:  map 0% reduce 0%
13/11/26 15:20:09 INFO mapreduce.Job:  map 1% reduce 0%
13/11/26 15:20:10 INFO mapreduce.Job:  map 10% reduce 0%
13/11/26 15:20:11 INFO mapreduce.Job:  map 14% reduce 0%
13/11/26 15:20:13 INFO mapreduce.Job:  map 18% reduce 0%
13/11/26 15:20:14 INFO mapreduce.Job:  map 21% reduce 0%
13/11/26 15:20:16 INFO mapreduce.Job:  map 22% reduce 0%
13/11/26 15:20:17 INFO mapreduce.Job:  map 23% reduce 0%
13/11/26 15:20:21 INFO mapreduce.Job:  map 24% reduce 0%
13/11/26 15:20:22 INFO mapreduce.Job:  map 26% reduce 0%
13/11/26 15:20:23 INFO mapreduce.Job:  map 27% reduce 0%
13/11/26 15:20:26 INFO mapreduce.Job:  map 31% reduce 0%
13/11/26 15:20:29 INFO mapreduce.Job:  map 34% reduce 0%
13/11/26 15:20:32 INFO mapreduce.Job:  map 38% reduce 0%
13/11/26 15:20:33 INFO mapreduce.Job:  map 39% reduce 0%
13/11/26 15:20:34 INFO mapreduce.Job:  map 40% reduce 0%
13/11/26 15:20:35 INFO mapreduce.Job:  map 44% reduce 0%
13/11/26 15:20:38 INFO mapreduce.Job:  map 46% reduce 0%
13/11/26 15:20:40 INFO mapreduce.Job:  map 47% reduce 0%
13/11/26 15:20:44 INFO mapreduce.Job:  map 48% reduce 1%
13/11/26 15:20:45 INFO mapreduce.Job:  map 50% reduce 1%
13/11/26 15:20:46 INFO mapreduce.Job:  map 51% reduce 1%
13/11/26 15:20:47 INFO mapreduce.Job:  map 52% reduce 1%
13/11/26 15:20:48 INFO mapreduce.Job:  map 53% reduce 1%
13/11/26 15:20:50 INFO mapreduce.Job:  map 59% reduce 4%
13/11/26 15:20:53 INFO mapreduce.Job:  map 61% reduce 4%
13/11/26 15:20:54 INFO mapreduce.Job:  map 62% reduce 4%
13/11/26 15:20:56 INFO mapreduce.Job:  map 63% reduce 4%
13/11/26 15:20:57 INFO mapreduce.Job:  map 63% reduce 6%
13/11/26 15:20:59 INFO mapreduce.Job:  map 66% reduce 6%
13/11/26 15:21:00 INFO mapreduce.Job:  map 69% reduce 7%
13/11/26 15:21:02 INFO mapreduce.Job:  map 70% reduce 8%
13/11/26 15:21:05 INFO mapreduce.Job:  map 71% reduce 9%
13/11/26 15:21:10 INFO mapreduce.Job:  map 72% reduce 11%
13/11/26 15:21:11 INFO mapreduce.Job:  map 74% reduce 11%
13/11/26 15:21:12 INFO mapreduce.Job:  map 75% reduce 11%
13/11/26 15:21:13 INFO mapreduce.Job:  map 76% reduce 12%
13/11/26 15:21:14 INFO mapreduce.Job:  map 77% reduce 12%
13/11/26 15:21:15 INFO mapreduce.Job:  map 79% reduce 12%
13/11/26 15:21:16 INFO mapreduce.Job:  map 80% reduce 12%
13/11/26 15:21:19 INFO mapreduce.Job:  map 82% reduce 12%
13/11/26 15:21:20 INFO mapreduce.Job:  map 84% reduce 13%
13/11/26 15:21:21 INFO mapreduce.Job:  map 86% reduce 13%
13/11/26 15:21:22 INFO mapreduce.Job:  map 87% reduce 13%
13/11/26 15:21:23 INFO mapreduce.Job:  map 90% reduce 14%
13/11/26 15:21:25 INFO mapreduce.Job:  map 91% reduce 15%
13/11/26 15:21:26 INFO mapreduce.Job:  map 92% reduce 15%
13/11/26 15:21:27 INFO mapreduce.Job:  map 95% reduce 15%
13/11/26 15:21:28 INFO mapreduce.Job:  map 97% reduce 16%
13/11/26 15:21:29 INFO mapreduce.Job:  map 98% reduce 16%
13/11/26 15:21:30 INFO mapreduce.Job:  map 100% reduce 16%
13/11/26 15:21:33 INFO mapreduce.Job:  map 100% reduce 18%
13/11/26 15:21:34 INFO mapreduce.Job:  map 100% reduce 19%
13/11/26 15:21:36 INFO mapreduce.Job:  map 100% reduce 21%
13/11/26 15:21:37 INFO mapreduce.Job:  map 100% reduce 22%
13/11/26 15:21:38 INFO mapreduce.Job:  map 100% reduce 23%
13/11/26 15:21:40 INFO mapreduce.Job:  map 100% reduce 25%
13/11/26 15:21:43 INFO mapreduce.Job:  map 100% reduce 27%
13/11/26 15:21:46 INFO mapreduce.Job:  map 100% reduce 29%
13/11/26 15:21:48 INFO mapreduce.Job:  map 100% reduce 30%
13/11/26 15:21:49 INFO mapreduce.Job:  map 100% reduce 31%
13/11/26 15:21:51 INFO mapreduce.Job:  map 100% reduce 32%
13/11/26 15:21:58 INFO mapreduce.Job:  map 100% reduce 33%
13/11/26 15:22:03 INFO mapreduce.Job:  map 100% reduce 34%
13/11/26 15:22:07 INFO mapreduce.Job:  map 100% reduce 36%
13/11/26 15:22:10 INFO mapreduce.Job:  map 100% reduce 37%
13/11/26 15:22:13 INFO mapreduce.Job:  map 100% reduce 38%
13/11/26 15:22:21 INFO mapreduce.Job:  map 100% reduce 39%
13/11/26 15:22:31 INFO mapreduce.Job:  map 100% reduce 40%
13/11/26 15:22:40 INFO mapreduce.Job:  map 100% reduce 41%
13/11/26 15:22:43 INFO mapreduce.Job:  map 100% reduce 42%
13/11/26 15:22:46 INFO mapreduce.Job:  map 100% reduce 43%
13/11/26 15:22:49 INFO mapreduce.Job:  map 100% reduce 45%
13/11/26 15:22:53 INFO mapreduce.Job:  map 100% reduce 46%
13/11/26 15:23:02 INFO mapreduce.Job:  map 100% reduce 47%
13/11/26 15:23:04 INFO mapreduce.Job:  map 100% reduce 48%
13/11/26 15:23:07 INFO mapreduce.Job:  map 100% reduce 49%
13/11/26 15:23:08 INFO mapreduce.Job:  map 100% reduce 50%
13/11/26 15:23:10 INFO mapreduce.Job:  map 100% reduce 51%
13/11/26 15:23:13 INFO mapreduce.Job:  map 100% reduce 52%
13/11/26 15:23:17 INFO mapreduce.Job:  map 100% reduce 53%
13/11/26 15:23:23 INFO mapreduce.Job:  map 100% reduce 54%
13/11/26 15:23:28 INFO mapreduce.Job:  map 100% reduce 55%
13/11/26 15:23:31 INFO mapreduce.Job:  map 100% reduce 56%
13/11/26 15:23:32 INFO mapreduce.Job:  map 100% reduce 58%
13/11/26 15:23:34 INFO mapreduce.Job:  map 100% reduce 59%
13/11/26 15:23:35 INFO mapreduce.Job:  map 100% reduce 60%
13/11/26 15:23:37 INFO mapreduce.Job:  map 100% reduce 61%
13/11/26 15:23:38 INFO mapreduce.Job:  map 100% reduce 63%
13/11/26 15:23:42 INFO mapreduce.Job:  map 100% reduce 65%
13/11/26 15:23:45 INFO mapreduce.Job:  map 100% reduce 67%
13/11/26 15:23:49 INFO mapreduce.Job:  map 100% reduce 68%
13/11/26 15:23:50 INFO mapreduce.Job:  map 100% reduce 69%
13/11/26 15:23:53 INFO mapreduce.Job:  map 100% reduce 70%
13/11/26 15:23:56 INFO mapreduce.Job:  map 100% reduce 71%
13/11/26 15:24:00 INFO mapreduce.Job:  map 100% reduce 72%
13/11/26 15:24:04 INFO mapreduce.Job:  map 100% reduce 73%
13/11/26 15:24:07 INFO mapreduce.Job:  map 100% reduce 74%
13/11/26 15:24:08 INFO mapreduce.Job:  map 100% reduce 75%
13/11/26 15:24:09 INFO mapreduce.Job:  map 100% reduce 76%
13/11/26 15:24:10 INFO mapreduce.Job:  map 100% reduce 77%
13/11/26 15:24:11 INFO mapreduce.Job:  map 100% reduce 78%
13/11/26 15:24:12 INFO mapreduce.Job:  map 100% reduce 79%
13/11/26 15:24:13 INFO mapreduce.Job:  map 100% reduce 80%
13/11/26 15:24:14 INFO mapreduce.Job:  map 100% reduce 81%
13/11/26 15:24:16 INFO mapreduce.Job:  map 100% reduce 82%
13/11/26 15:24:17 INFO mapreduce.Job:  map 100% reduce 83%
13/11/26 15:24:19 INFO mapreduce.Job:  map 100% reduce 84%
13/11/26 15:24:23 INFO mapreduce.Job:  map 100% reduce 85%
13/11/26 15:24:29 INFO mapreduce.Job:  map 100% reduce 86%
13/11/26 15:24:35 INFO mapreduce.Job:  map 100% reduce 87%
13/11/26 15:24:41 INFO mapreduce.Job:  map 100% reduce 88%
13/11/26 15:24:47 INFO mapreduce.Job:  map 100% reduce 89%
13/11/26 15:24:52 INFO mapreduce.Job:  map 100% reduce 90%
13/11/26 15:24:58 INFO mapreduce.Job:  map 100% reduce 91%
13/11/26 15:25:03 INFO mapreduce.Job:  map 100% reduce 92%
13/11/26 15:25:09 INFO mapreduce.Job:  map 100% reduce 93%
13/11/26 15:25:15 INFO mapreduce.Job:  map 100% reduce 94%
13/11/26 15:25:20 INFO mapreduce.Job:  map 100% reduce 95%
13/11/26 15:25:25 INFO mapreduce.Job:  map 100% reduce 96%
13/11/26 15:25:29 INFO mapreduce.Job:  map 100% reduce 97%
13/11/26 15:25:34 INFO mapreduce.Job:  map 100% reduce 98%
13/11/26 15:25:41 INFO mapreduce.Job:  map 100% reduce 99%
13/11/26 15:25:45 INFO mapreduce.Job:  map 100% reduce 100%
13/11/26 15:25:46 INFO mapreduce.Job: Job job_1384176415098_0183 completed successfully
13/11/26 15:25:46 INFO mapreduce.Job: Counters: 44
	File System Counters
		FILE: Number of bytes read=9923222111
		FILE: Number of bytes written=14994529223
		FILE: Number of read operations=0
		FILE: Number of large read operations=0
		FILE: Number of write operations=0
		HDFS: Number of bytes read=3314727509
		HDFS: Number of bytes written=2078529814
		HDFS: Number of read operations=189
		HDFS: Number of large read operations=0
		HDFS: Number of write operations=20
	Job Counters 
		Killed map tasks=1
		Launched map tasks=54
		Launched reduce tasks=10
		Rack-local map tasks=54
		Total time spent by all maps in occupied slots (ms)=3037144
		Total time spent by all reduces in occupied slots (ms)=7565340
	Map-Reduce Framework
		Map input records=13420615
		Map output records=115034816
		Map output bytes=4838094014
		Map output materialized bytes=5068193754
		Input split bytes=6201
		Combine input records=0
		Combine output records=0
		Reduce input groups=13420615
		Reduce shuffle bytes=5068193754
		Reduce input records=115034816
		Reduce output records=13420615
		Spilled Records=339491713
		Shuffled Maps =530
		Failed Shuffles=0
		Merged Map outputs=530
		GC time elapsed (ms)=15389
		CPU time spent (ms)=1886740
		Physical memory (bytes) snapshot=29119389696
		Virtual memory (bytes) snapshot=117331714048
		Total committed heap usage (bytes)=36845256704
	Shuffle Errors
		BAD_ID=0
		CONNECTION=0
		IO_ERROR=0
		WRONG_LENGTH=0
		WRONG_MAP=0
		WRONG_REDUCE=0
	File Input Format Counters 
		Bytes Read=3314721308
	File Output Format Counters 
		Bytes Written=2078529814
13/11/26 15:25:46 INFO streaming.StreamJob: Output directory: /user/huangxuangui/step2/out21
13/11/26 15:25:47 WARN conf.Configuration: mapred.reduce.tasks is deprecated. Instead, use mapreduce.job.reduces
packageJobJar: [/srv/hadoop/hadoop/hadoop-unjar1840708128819514005/] [] /tmp/streamjob3267272484196067261.jar tmpDir=null
13/11/26 15:25:47 INFO service.AbstractService: Service:org.apache.hadoop.yarn.client.YarnClientImpl is inited.
13/11/26 15:25:47 INFO service.AbstractService: Service:org.apache.hadoop.yarn.client.YarnClientImpl is started.
13/11/26 15:25:48 INFO service.AbstractService: Service:org.apache.hadoop.yarn.client.YarnClientImpl is inited.
13/11/26 15:25:48 INFO service.AbstractService: Service:org.apache.hadoop.yarn.client.YarnClientImpl is started.
13/11/26 15:25:48 INFO mapred.FileInputFormat: Total input paths to process : 10
13/11/26 15:25:48 INFO net.NetworkTopology: Adding a new node: /default-rack/192.168.1.150:50010
13/11/26 15:25:48 INFO net.NetworkTopology: Adding a new node: /default-rack/192.168.1.200:50010
13/11/26 15:25:48 INFO mapreduce.JobSubmitter: number of splits:33
13/11/26 15:25:48 WARN conf.Configuration: mapred.jar is deprecated. Instead, use mapreduce.job.jar
13/11/26 15:25:48 WARN conf.Configuration: mapred.cache.files is deprecated. Instead, use mapreduce.job.cache.files
13/11/26 15:25:48 WARN conf.Configuration: mapred.output.value.class is deprecated. Instead, use mapreduce.job.output.value.class
13/11/26 15:25:48 WARN conf.Configuration: mapred.mapoutput.value.class is deprecated. Instead, use mapreduce.map.output.value.class
13/11/26 15:25:48 WARN conf.Configuration: mapred.used.genericoptionsparser is deprecated. Instead, use mapreduce.client.genericoptionsparser.used
13/11/26 15:25:48 WARN conf.Configuration: mapred.job.name is deprecated. Instead, use mapreduce.job.name
13/11/26 15:25:48 WARN conf.Configuration: mapred.input.dir is deprecated. Instead, use mapreduce.input.fileinputformat.inputdir
13/11/26 15:25:48 WARN conf.Configuration: mapred.output.dir is deprecated. Instead, use mapreduce.output.fileoutputformat.outputdir
13/11/26 15:25:48 WARN conf.Configuration: mapred.map.tasks is deprecated. Instead, use mapreduce.job.maps
13/11/26 15:25:48 WARN conf.Configuration: mapred.cache.files.timestamps is deprecated. Instead, use mapreduce.job.cache.files.timestamps
13/11/26 15:25:48 WARN conf.Configuration: mapred.output.key.class is deprecated. Instead, use mapreduce.job.output.key.class
13/11/26 15:25:48 WARN conf.Configuration: mapred.mapoutput.key.class is deprecated. Instead, use mapreduce.map.output.key.class
13/11/26 15:25:48 WARN conf.Configuration: mapred.working.dir is deprecated. Instead, use mapreduce.job.working.dir
13/11/26 15:25:48 INFO mapreduce.JobSubmitter: Submitting tokens for job: job_1384176415098_0184
13/11/26 15:25:49 INFO client.YarnClientImpl: Submitted application application_1384176415098_0184 to ResourceManager at workstation/192.168.1.150:8032
13/11/26 15:25:49 INFO mapreduce.Job: The url to track the job: http://workstation.mshome.net:8043/proxy/application_1384176415098_0184/
13/11/26 15:25:49 INFO mapreduce.Job: Running job: job_1384176415098_0184
13/11/26 15:25:54 INFO mapreduce.Job: Job job_1384176415098_0184 running in uber mode : false
13/11/26 15:25:54 INFO mapreduce.Job:  map 0% reduce 0%
13/11/26 15:26:07 INFO mapreduce.Job:  map 1% reduce 0%
13/11/26 15:26:08 INFO mapreduce.Job:  map 7% reduce 0%
13/11/26 15:26:10 INFO mapreduce.Job:  map 8% reduce 0%
13/11/26 15:26:11 INFO mapreduce.Job:  map 12% reduce 0%
13/11/26 15:26:14 INFO mapreduce.Job:  map 15% reduce 0%
13/11/26 15:26:15 INFO mapreduce.Job:  map 17% reduce 0%
13/11/26 15:26:17 INFO mapreduce.Job:  map 19% reduce 0%
13/11/26 15:26:18 INFO mapreduce.Job:  map 20% reduce 0%
13/11/26 15:26:23 INFO mapreduce.Job:  map 21% reduce 0%
13/11/26 15:26:24 INFO mapreduce.Job:  map 23% reduce 0%
13/11/26 15:26:26 INFO mapreduce.Job:  map 25% reduce 0%
13/11/26 15:26:27 INFO mapreduce.Job:  map 27% reduce 0%
13/11/26 15:26:28 INFO mapreduce.Job:  map 28% reduce 0%
13/11/26 15:26:29 INFO mapreduce.Job:  map 30% reduce 0%
13/11/26 15:26:30 INFO mapreduce.Job:  map 31% reduce 0%
13/11/26 15:26:31 INFO mapreduce.Job:  map 33% reduce 0%
13/11/26 15:26:32 INFO mapreduce.Job:  map 34% reduce 0%
13/11/26 15:26:34 INFO mapreduce.Job:  map 35% reduce 0%
13/11/26 15:26:37 INFO mapreduce.Job:  map 36% reduce 0%
13/11/26 15:26:38 INFO mapreduce.Job:  map 37% reduce 0%
13/11/26 15:26:40 INFO mapreduce.Job:  map 38% reduce 0%
13/11/26 15:26:41 INFO mapreduce.Job:  map 40% reduce 0%
13/11/26 15:26:42 INFO mapreduce.Job:  map 41% reduce 0%
13/11/26 15:26:43 INFO mapreduce.Job:  map 42% reduce 0%
13/11/26 15:26:44 INFO mapreduce.Job:  map 44% reduce 0%
13/11/26 15:26:46 INFO mapreduce.Job:  map 45% reduce 0%
13/11/26 15:26:49 INFO mapreduce.Job:  map 47% reduce 0%
13/11/26 15:26:51 INFO mapreduce.Job:  map 48% reduce 0%
13/11/26 15:26:52 INFO mapreduce.Job:  map 50% reduce 0%
13/11/26 15:26:53 INFO mapreduce.Job:  map 51% reduce 0%
13/11/26 15:26:54 INFO mapreduce.Job:  map 52% reduce 0%
13/11/26 15:26:55 INFO mapreduce.Job:  map 56% reduce 0%
13/11/26 15:26:57 INFO mapreduce.Job:  map 58% reduce 0%
13/11/26 15:26:58 INFO mapreduce.Job:  map 61% reduce 0%
13/11/26 15:27:00 INFO mapreduce.Job:  map 64% reduce 0%
13/11/26 15:27:02 INFO mapreduce.Job:  map 65% reduce 0%
13/11/26 15:27:03 INFO mapreduce.Job:  map 66% reduce 0%
13/11/26 15:27:05 INFO mapreduce.Job:  map 67% reduce 0%
13/11/26 15:27:06 INFO mapreduce.Job:  map 70% reduce 0%
13/11/26 15:27:07 INFO mapreduce.Job:  map 71% reduce 0%
13/11/26 15:27:08 INFO mapreduce.Job:  map 71% reduce 1%
13/11/26 15:27:09 INFO mapreduce.Job:  map 73% reduce 1%
13/11/26 15:27:10 INFO mapreduce.Job:  map 73% reduce 4%
13/11/26 15:27:13 INFO mapreduce.Job:  map 73% reduce 5%
13/11/26 15:27:15 INFO mapreduce.Job:  map 74% reduce 5%
13/11/26 15:27:16 INFO mapreduce.Job:  map 75% reduce 5%
13/11/26 15:27:18 INFO mapreduce.Job:  map 76% reduce 5%
13/11/26 15:27:20 INFO mapreduce.Job:  map 76% reduce 6%
13/11/26 15:27:22 INFO mapreduce.Job:  map 77% reduce 6%
13/11/26 15:27:24 INFO mapreduce.Job:  map 77% reduce 7%
13/11/26 15:27:25 INFO mapreduce.Job:  map 78% reduce 7%
13/11/26 15:27:27 INFO mapreduce.Job:  map 79% reduce 7%
13/11/26 15:27:31 INFO mapreduce.Job:  map 81% reduce 7%
13/11/26 15:27:32 INFO mapreduce.Job:  map 82% reduce 9%
13/11/26 15:27:33 INFO mapreduce.Job:  map 91% reduce 10%
13/11/26 15:27:34 INFO mapreduce.Job:  map 93% reduce 11%
13/11/26 15:27:37 INFO mapreduce.Job:  map 94% reduce 13%
13/11/26 15:27:40 INFO mapreduce.Job:  map 94% reduce 15%
13/11/26 15:27:41 INFO mapreduce.Job:  map 94% reduce 16%
13/11/26 15:27:42 INFO mapreduce.Job:  map 94% reduce 18%
13/11/26 15:27:44 INFO mapreduce.Job:  map 95% reduce 18%
13/11/26 15:27:46 INFO mapreduce.Job:  map 96% reduce 19%
13/11/26 15:27:50 INFO mapreduce.Job:  map 97% reduce 19%
13/11/26 15:27:54 INFO mapreduce.Job:  map 98% reduce 19%
13/11/26 15:27:56 INFO mapreduce.Job:  map 98% reduce 20%
13/11/26 15:27:57 INFO mapreduce.Job:  map 99% reduce 20%
13/11/26 15:28:00 INFO mapreduce.Job:  map 100% reduce 20%
13/11/26 15:28:01 INFO mapreduce.Job:  map 100% reduce 21%
13/11/26 15:28:04 INFO mapreduce.Job:  map 100% reduce 22%
13/11/26 15:28:09 INFO mapreduce.Job:  map 100% reduce 23%
13/11/26 15:28:16 INFO mapreduce.Job:  map 100% reduce 24%
13/11/26 15:28:17 INFO mapreduce.Job:  map 100% reduce 25%
13/11/26 15:28:21 INFO mapreduce.Job:  map 100% reduce 26%
13/11/26 15:28:24 INFO mapreduce.Job:  map 100% reduce 27%
13/11/26 15:28:27 INFO mapreduce.Job:  map 100% reduce 28%
13/11/26 15:28:34 INFO mapreduce.Job:  map 100% reduce 29%
13/11/26 15:28:39 INFO mapreduce.Job:  map 100% reduce 30%
13/11/26 15:28:46 INFO mapreduce.Job:  map 100% reduce 31%
13/11/26 15:28:55 INFO mapreduce.Job:  map 100% reduce 32%
13/11/26 15:28:56 INFO mapreduce.Job:  map 100% reduce 33%
13/11/26 15:28:58 INFO mapreduce.Job:  map 100% reduce 34%
13/11/26 15:28:59 INFO mapreduce.Job:  map 100% reduce 35%
13/11/26 15:29:00 INFO mapreduce.Job:  map 100% reduce 36%
13/11/26 15:29:01 INFO mapreduce.Job:  map 100% reduce 37%
13/11/26 15:29:04 INFO mapreduce.Job:  map 100% reduce 38%
13/11/26 15:29:05 INFO mapreduce.Job:  map 100% reduce 39%
13/11/26 15:29:08 INFO mapreduce.Job:  map 100% reduce 40%
13/11/26 15:29:09 INFO mapreduce.Job:  map 100% reduce 41%
13/11/26 15:29:10 INFO mapreduce.Job:  map 100% reduce 42%
13/11/26 15:29:13 INFO mapreduce.Job:  map 100% reduce 43%
13/11/26 15:29:16 INFO mapreduce.Job:  map 100% reduce 44%
13/11/26 15:29:18 INFO mapreduce.Job:  map 100% reduce 45%
13/11/26 15:29:25 INFO mapreduce.Job:  map 100% reduce 47%
13/11/26 15:29:28 INFO mapreduce.Job:  map 100% reduce 48%
13/11/26 15:29:29 INFO mapreduce.Job:  map 100% reduce 49%
13/11/26 15:29:33 INFO mapreduce.Job:  map 100% reduce 50%
13/11/26 15:29:38 INFO mapreduce.Job:  map 100% reduce 52%
13/11/26 15:29:40 INFO mapreduce.Job:  map 100% reduce 53%
13/11/26 15:29:42 INFO mapreduce.Job:  map 100% reduce 54%
13/11/26 15:29:43 INFO mapreduce.Job:  map 100% reduce 56%
13/11/26 15:29:45 INFO mapreduce.Job:  map 100% reduce 57%
13/11/26 15:29:47 INFO mapreduce.Job:  map 100% reduce 58%
13/11/26 15:29:48 INFO mapreduce.Job:  map 100% reduce 59%
13/11/26 15:29:55 INFO mapreduce.Job:  map 100% reduce 60%
13/11/26 15:29:59 INFO mapreduce.Job:  map 100% reduce 62%
13/11/26 15:30:02 INFO mapreduce.Job:  map 100% reduce 64%
13/11/26 15:30:05 INFO mapreduce.Job:  map 100% reduce 65%
13/11/26 15:30:08 INFO mapreduce.Job:  map 100% reduce 66%
13/11/26 15:30:10 INFO mapreduce.Job:  map 100% reduce 67%
13/11/26 15:30:11 INFO mapreduce.Job:  map 100% reduce 68%
13/11/26 15:30:14 INFO mapreduce.Job:  map 100% reduce 69%
13/11/26 15:30:15 INFO mapreduce.Job:  map 100% reduce 70%
13/11/26 15:30:17 INFO mapreduce.Job:  map 100% reduce 71%
13/11/26 15:30:18 INFO mapreduce.Job:  map 100% reduce 72%
13/11/26 15:30:20 INFO mapreduce.Job:  map 100% reduce 73%
13/11/26 15:30:22 INFO mapreduce.Job:  map 100% reduce 74%
13/11/26 15:30:23 INFO mapreduce.Job:  map 100% reduce 75%
13/11/26 15:30:25 INFO mapreduce.Job:  map 100% reduce 76%
13/11/26 15:30:29 INFO mapreduce.Job:  map 100% reduce 77%
13/11/26 15:30:35 INFO mapreduce.Job:  map 100% reduce 78%
13/11/26 15:30:41 INFO mapreduce.Job:  map 100% reduce 79%
13/11/26 15:30:47 INFO mapreduce.Job:  map 100% reduce 80%
13/11/26 15:30:53 INFO mapreduce.Job:  map 100% reduce 81%
13/11/26 15:30:59 INFO mapreduce.Job:  map 100% reduce 82%
13/11/26 15:31:04 INFO mapreduce.Job:  map 100% reduce 83%
13/11/26 15:31:10 INFO mapreduce.Job:  map 100% reduce 84%
13/11/26 15:31:16 INFO mapreduce.Job:  map 100% reduce 85%
13/11/26 15:31:21 INFO mapreduce.Job:  map 100% reduce 86%
13/11/26 15:31:26 INFO mapreduce.Job:  map 100% reduce 87%
13/11/26 15:31:30 INFO mapreduce.Job:  map 100% reduce 88%
13/11/26 15:31:36 INFO mapreduce.Job:  map 100% reduce 89%
13/11/26 15:31:41 INFO mapreduce.Job:  map 100% reduce 90%
13/11/26 15:31:47 INFO mapreduce.Job:  map 100% reduce 91%
13/11/26 15:31:53 INFO mapreduce.Job:  map 100% reduce 92%
13/11/26 15:31:59 INFO mapreduce.Job:  map 100% reduce 93%
13/11/26 15:32:05 INFO mapreduce.Job:  map 100% reduce 94%
13/11/26 15:32:10 INFO mapreduce.Job:  map 100% reduce 95%
13/11/26 15:32:16 INFO mapreduce.Job:  map 100% reduce 96%
13/11/26 15:32:26 INFO mapreduce.Job:  map 100% reduce 97%
13/11/26 15:32:35 INFO mapreduce.Job:  map 100% reduce 98%
13/11/26 15:32:43 INFO mapreduce.Job:  map 100% reduce 99%
13/11/26 15:32:54 INFO mapreduce.Job:  map 100% reduce 100%
13/11/26 15:33:03 INFO mapreduce.Job: Job job_1384176415098_0184 completed successfully
13/11/26 15:33:03 INFO mapreduce.Job: Counters: 43
	File System Counters
		FILE: Number of bytes read=12396793743
		FILE: Number of bytes written=18623834882
		FILE: Number of read operations=0
		FILE: Number of large read operations=0
		FILE: Number of write operations=0
		HDFS: Number of bytes read=2078832683
		HDFS: Number of bytes written=3256623844
		HDFS: Number of read operations=129
		HDFS: Number of large read operations=0
		HDFS: Number of write operations=20
	Job Counters 
		Launched map tasks=33
		Launched reduce tasks=10
		Rack-local map tasks=33
		Total time spent by all maps in occupied slots (ms)=3888924
		Total time spent by all reduces in occupied slots (ms)=9420393
	Map-Reduce Framework
		Map input records=13420615
		Map output records=115034816
		Map output bytes=5995553374
		Map output materialized bytes=6225657299
		Input split bytes=3861
		Combine input records=0
		Combine output records=0
		Reduce input groups=13420615
		Reduce shuffle bytes=6225657299
		Reduce input records=115034816
		Reduce output records=13420615
		Spilled Records=343953277
		Shuffled Maps =330
		Failed Shuffles=0
		Merged Map outputs=330
		GC time elapsed (ms)=19442
		CPU time spent (ms)=2528110
		Physical memory (bytes) snapshot=27169513472
		Virtual memory (bytes) snapshot=85387296768
		Total committed heap usage (bytes)=32212779008
	Shuffle Errors
		BAD_ID=0
		CONNECTION=0
		IO_ERROR=0
		WRONG_LENGTH=0
		WRONG_MAP=0
		WRONG_REDUCE=0
	File Input Format Counters 
		Bytes Read=2078828822
	File Output Format Counters 
		Bytes Written=3256623844
13/11/26 15:33:03 INFO streaming.StreamJob: Output directory: /user/huangxuangui/step2/out30
13/11/26 15:33:04 WARN conf.Configuration: mapred.reduce.tasks is deprecated. Instead, use mapreduce.job.reduces
packageJobJar: [/srv/hadoop/hadoop/hadoop-unjar4607017655005246710/] [] /tmp/streamjob6283422214541835768.jar tmpDir=null
13/11/26 15:33:04 INFO service.AbstractService: Service:org.apache.hadoop.yarn.client.YarnClientImpl is inited.
13/11/26 15:33:04 INFO service.AbstractService: Service:org.apache.hadoop.yarn.client.YarnClientImpl is started.
13/11/26 15:33:04 INFO service.AbstractService: Service:org.apache.hadoop.yarn.client.YarnClientImpl is inited.
13/11/26 15:33:04 INFO service.AbstractService: Service:org.apache.hadoop.yarn.client.YarnClientImpl is started.
13/11/26 15:33:05 INFO mapred.FileInputFormat: Total input paths to process : 10
13/11/26 15:33:05 INFO net.NetworkTopology: Adding a new node: /default-rack/192.168.1.150:50010
13/11/26 15:33:05 INFO net.NetworkTopology: Adding a new node: /default-rack/192.168.1.200:50010
13/11/26 15:33:05 INFO mapreduce.JobSubmitter: number of splits:53
13/11/26 15:33:05 WARN conf.Configuration: mapred.jar is deprecated. Instead, use mapreduce.job.jar
13/11/26 15:33:05 WARN conf.Configuration: mapred.cache.files is deprecated. Instead, use mapreduce.job.cache.files
13/11/26 15:33:05 WARN conf.Configuration: mapred.output.value.class is deprecated. Instead, use mapreduce.job.output.value.class
13/11/26 15:33:05 WARN conf.Configuration: mapred.mapoutput.value.class is deprecated. Instead, use mapreduce.map.output.value.class
13/11/26 15:33:05 WARN conf.Configuration: mapred.used.genericoptionsparser is deprecated. Instead, use mapreduce.client.genericoptionsparser.used
13/11/26 15:33:05 WARN conf.Configuration: mapred.job.name is deprecated. Instead, use mapreduce.job.name
13/11/26 15:33:05 WARN conf.Configuration: mapred.input.dir is deprecated. Instead, use mapreduce.input.fileinputformat.inputdir
13/11/26 15:33:05 WARN conf.Configuration: mapred.output.dir is deprecated. Instead, use mapreduce.output.fileoutputformat.outputdir
13/11/26 15:33:05 WARN conf.Configuration: mapred.map.tasks is deprecated. Instead, use mapreduce.job.maps
13/11/26 15:33:05 WARN conf.Configuration: mapred.cache.files.timestamps is deprecated. Instead, use mapreduce.job.cache.files.timestamps
13/11/26 15:33:05 WARN conf.Configuration: mapred.output.key.class is deprecated. Instead, use mapreduce.job.output.key.class
13/11/26 15:33:05 WARN conf.Configuration: mapred.mapoutput.key.class is deprecated. Instead, use mapreduce.map.output.key.class
13/11/26 15:33:05 WARN conf.Configuration: mapred.working.dir is deprecated. Instead, use mapreduce.job.working.dir
13/11/26 15:33:05 INFO mapreduce.JobSubmitter: Submitting tokens for job: job_1384176415098_0185
13/11/26 15:33:06 INFO client.YarnClientImpl: Submitted application application_1384176415098_0185 to ResourceManager at workstation/192.168.1.150:8032
13/11/26 15:33:06 INFO mapreduce.Job: The url to track the job: http://workstation.mshome.net:8043/proxy/application_1384176415098_0185/
13/11/26 15:33:06 INFO mapreduce.Job: Running job: job_1384176415098_0185
13/11/26 15:33:11 INFO mapreduce.Job: Job job_1384176415098_0185 running in uber mode : false
13/11/26 15:33:11 INFO mapreduce.Job:  map 0% reduce 0%
13/11/26 15:33:26 INFO mapreduce.Job:  map 8% reduce 0%
13/11/26 15:33:27 INFO mapreduce.Job:  map 13% reduce 0%
13/11/26 15:33:28 INFO mapreduce.Job:  map 14% reduce 0%
13/11/26 15:33:29 INFO mapreduce.Job:  map 17% reduce 0%
13/11/26 15:33:30 INFO mapreduce.Job:  map 21% reduce 0%
13/11/26 15:33:32 INFO mapreduce.Job:  map 22% reduce 0%
13/11/26 15:33:33 INFO mapreduce.Job:  map 23% reduce 0%
13/11/26 15:33:38 INFO mapreduce.Job:  map 24% reduce 0%
13/11/26 15:33:39 INFO mapreduce.Job:  map 26% reduce 0%
13/11/26 15:33:40 INFO mapreduce.Job:  map 27% reduce 0%
13/11/26 15:33:41 INFO mapreduce.Job:  map 29% reduce 0%
13/11/26 15:33:42 INFO mapreduce.Job:  map 30% reduce 0%
13/11/26 15:33:43 INFO mapreduce.Job:  map 31% reduce 0%
13/11/26 15:33:44 INFO mapreduce.Job:  map 32% reduce 0%
13/11/26 15:33:45 INFO mapreduce.Job:  map 33% reduce 0%
13/11/26 15:33:47 INFO mapreduce.Job:  map 35% reduce 0%
13/11/26 15:33:48 INFO mapreduce.Job:  map 37% reduce 0%
13/11/26 15:33:49 INFO mapreduce.Job:  map 41% reduce 0%
13/11/26 15:33:50 INFO mapreduce.Job:  map 42% reduce 0%
13/11/26 15:33:52 INFO mapreduce.Job:  map 43% reduce 0%
13/11/26 15:33:54 INFO mapreduce.Job:  map 44% reduce 0%
13/11/26 15:33:55 INFO mapreduce.Job:  map 45% reduce 0%
13/11/26 15:33:56 INFO mapreduce.Job:  map 46% reduce 0%
13/11/26 15:33:57 INFO mapreduce.Job:  map 47% reduce 0%
13/11/26 15:33:59 INFO mapreduce.Job:  map 48% reduce 0%
13/11/26 15:34:00 INFO mapreduce.Job:  map 49% reduce 0%
13/11/26 15:34:01 INFO mapreduce.Job:  map 51% reduce 3%
13/11/26 15:34:03 INFO mapreduce.Job:  map 52% reduce 3%
13/11/26 15:34:04 INFO mapreduce.Job:  map 53% reduce 4%
13/11/26 15:34:05 INFO mapreduce.Job:  map 54% reduce 4%
13/11/26 15:34:07 INFO mapreduce.Job:  map 55% reduce 5%
13/11/26 15:34:08 INFO mapreduce.Job:  map 58% reduce 5%
13/11/26 15:34:09 INFO mapreduce.Job:  map 59% reduce 6%
13/11/26 15:34:10 INFO mapreduce.Job:  map 60% reduce 7%
13/11/26 15:34:13 INFO mapreduce.Job:  map 62% reduce 7%
13/11/26 15:34:15 INFO mapreduce.Job:  map 64% reduce 7%
13/11/26 15:34:16 INFO mapreduce.Job:  map 67% reduce 8%
13/11/26 15:34:17 INFO mapreduce.Job:  map 68% reduce 8%
13/11/26 15:34:18 INFO mapreduce.Job:  map 69% reduce 9%
13/11/26 15:34:21 INFO mapreduce.Job:  map 71% reduce 9%
13/11/26 15:34:22 INFO mapreduce.Job:  map 71% reduce 10%
13/11/26 15:34:23 INFO mapreduce.Job:  map 72% reduce 10%
13/11/26 15:34:24 INFO mapreduce.Job:  map 72% reduce 12%
13/11/26 15:34:26 INFO mapreduce.Job:  map 74% reduce 12%
13/11/26 15:34:27 INFO mapreduce.Job:  map 76% reduce 12%
13/11/26 15:34:28 INFO mapreduce.Job:  map 77% reduce 13%
13/11/26 15:34:29 INFO mapreduce.Job:  map 79% reduce 13%
13/11/26 15:34:31 INFO mapreduce.Job:  map 80% reduce 13%
13/11/26 15:34:32 INFO mapreduce.Job:  map 83% reduce 13%
13/11/26 15:34:33 INFO mapreduce.Job:  map 85% reduce 13%
13/11/26 15:34:34 INFO mapreduce.Job:  map 85% reduce 14%
13/11/26 15:34:35 INFO mapreduce.Job:  map 86% reduce 14%
13/11/26 15:34:37 INFO mapreduce.Job:  map 88% reduce 14%
13/11/26 15:34:38 INFO mapreduce.Job:  map 93% reduce 15%
13/11/26 15:34:39 INFO mapreduce.Job:  map 94% reduce 15%
13/11/26 15:34:40 INFO mapreduce.Job:  map 94% reduce 17%
13/11/26 15:34:42 INFO mapreduce.Job:  map 94% reduce 18%
13/11/26 15:34:44 INFO mapreduce.Job:  map 98% reduce 18%
13/11/26 15:34:46 INFO mapreduce.Job:  map 99% reduce 19%
13/11/26 15:34:48 INFO mapreduce.Job:  map 100% reduce 19%
13/11/26 15:34:49 INFO mapreduce.Job:  map 100% reduce 24%
13/11/26 15:34:50 INFO mapreduce.Job:  map 100% reduce 25%
13/11/26 15:34:58 INFO mapreduce.Job:  map 100% reduce 26%
13/11/26 15:34:59 INFO mapreduce.Job:  map 100% reduce 27%
13/11/26 15:35:02 INFO mapreduce.Job:  map 100% reduce 29%
13/11/26 15:35:05 INFO mapreduce.Job:  map 100% reduce 32%
13/11/26 15:35:06 INFO mapreduce.Job:  map 100% reduce 33%
13/11/26 15:35:08 INFO mapreduce.Job:  map 100% reduce 34%
13/11/26 15:35:10 INFO mapreduce.Job:  map 100% reduce 35%
13/11/26 15:35:11 INFO mapreduce.Job:  map 100% reduce 36%
13/11/26 15:35:13 INFO mapreduce.Job:  map 100% reduce 38%
13/11/26 15:35:16 INFO mapreduce.Job:  map 100% reduce 41%
13/11/26 15:35:20 INFO mapreduce.Job:  map 100% reduce 42%
13/11/26 15:35:21 INFO mapreduce.Job:  map 100% reduce 43%
13/11/26 15:35:22 INFO mapreduce.Job:  map 100% reduce 44%
13/11/26 15:35:28 INFO mapreduce.Job:  map 100% reduce 45%
13/11/26 15:35:30 INFO mapreduce.Job:  map 100% reduce 46%
13/11/26 15:35:33 INFO mapreduce.Job:  map 100% reduce 47%
13/11/26 15:35:35 INFO mapreduce.Job:  map 100% reduce 48%
13/11/26 15:35:37 INFO mapreduce.Job:  map 100% reduce 49%
13/11/26 15:35:39 INFO mapreduce.Job:  map 100% reduce 50%
13/11/26 15:35:41 INFO mapreduce.Job:  map 100% reduce 51%
13/11/26 15:35:43 INFO mapreduce.Job:  map 100% reduce 52%
13/11/26 15:35:44 INFO mapreduce.Job:  map 100% reduce 53%
13/11/26 15:35:46 INFO mapreduce.Job:  map 100% reduce 55%
13/11/26 15:35:49 INFO mapreduce.Job:  map 100% reduce 56%
13/11/26 15:35:50 INFO mapreduce.Job:  map 100% reduce 58%
13/11/26 15:35:51 INFO mapreduce.Job:  map 100% reduce 59%
13/11/26 15:35:52 INFO mapreduce.Job:  map 100% reduce 62%
13/11/26 15:35:54 INFO mapreduce.Job:  map 100% reduce 63%
13/11/26 15:35:56 INFO mapreduce.Job:  map 100% reduce 66%
13/11/26 15:35:59 INFO mapreduce.Job:  map 100% reduce 67%
13/11/26 15:36:02 INFO mapreduce.Job:  map 100% reduce 69%
13/11/26 15:36:05 INFO mapreduce.Job:  map 100% reduce 70%
13/11/26 15:36:09 INFO mapreduce.Job:  map 100% reduce 71%
13/11/26 15:36:14 INFO mapreduce.Job:  map 100% reduce 72%
13/11/26 15:36:17 INFO mapreduce.Job:  map 100% reduce 73%
13/11/26 15:36:20 INFO mapreduce.Job:  map 100% reduce 74%
13/11/26 15:36:26 INFO mapreduce.Job:  map 100% reduce 75%
13/11/26 15:36:30 INFO mapreduce.Job:  map 100% reduce 76%
13/11/26 15:36:35 INFO mapreduce.Job:  map 100% reduce 77%
13/11/26 15:36:36 INFO mapreduce.Job:  map 100% reduce 78%
13/11/26 15:36:38 INFO mapreduce.Job:  map 100% reduce 79%
13/11/26 15:36:41 INFO mapreduce.Job:  map 100% reduce 80%
13/11/26 15:36:42 INFO mapreduce.Job:  map 100% reduce 81%
13/11/26 15:36:44 INFO mapreduce.Job:  map 100% reduce 82%
13/11/26 15:36:45 INFO mapreduce.Job:  map 100% reduce 83%
13/11/26 15:36:47 INFO mapreduce.Job:  map 100% reduce 84%
13/11/26 15:36:50 INFO mapreduce.Job:  map 100% reduce 85%
13/11/26 15:36:53 INFO mapreduce.Job:  map 100% reduce 86%
13/11/26 15:36:54 INFO mapreduce.Job:  map 100% reduce 87%
13/11/26 15:36:57 INFO mapreduce.Job:  map 100% reduce 88%
13/11/26 15:37:00 INFO mapreduce.Job:  map 100% reduce 89%
13/11/26 15:37:04 INFO mapreduce.Job:  map 100% reduce 90%
13/11/26 15:37:05 INFO mapreduce.Job:  map 100% reduce 91%
13/11/26 15:37:08 INFO mapreduce.Job:  map 100% reduce 92%
13/11/26 15:37:13 INFO mapreduce.Job:  map 100% reduce 93%
13/11/26 15:37:17 INFO mapreduce.Job:  map 100% reduce 94%
13/11/26 15:37:21 INFO mapreduce.Job:  map 100% reduce 95%
13/11/26 15:37:23 INFO mapreduce.Job:  map 100% reduce 96%
13/11/26 15:37:26 INFO mapreduce.Job:  map 100% reduce 97%
13/11/26 15:37:28 INFO mapreduce.Job:  map 100% reduce 98%
13/11/26 15:37:33 INFO mapreduce.Job:  map 100% reduce 99%
13/11/26 15:37:43 INFO mapreduce.Job:  map 100% reduce 100%
13/11/26 15:37:43 INFO mapreduce.Job: Job job_1384176415098_0185 completed successfully
13/11/26 15:37:43 INFO mapreduce.Job: Counters: 43
	File System Counters
		FILE: Number of bytes read=9923241155
		FILE: Number of bytes written=14994553465
		FILE: Number of read operations=0
		FILE: Number of large read operations=0
		FILE: Number of write operations=0
		HDFS: Number of bytes read=3314731805
		HDFS: Number of bytes written=2078534110
		HDFS: Number of read operations=189
		HDFS: Number of large read operations=0
		HDFS: Number of write operations=20
	Job Counters 
		Launched map tasks=53
		Launched reduce tasks=10
		Rack-local map tasks=53
		Total time spent by all maps in occupied slots (ms)=2915804
		Total time spent by all reduces in occupied slots (ms)=5807478
	Map-Reduce Framework
		Map input records=13420615
		Map output records=115034816
		Map output bytes=4838102606
		Map output materialized bytes=5068202346
		Input split bytes=6201
		Combine input records=0
		Combine output records=0
		Reduce input groups=13420615
		Reduce shuffle bytes=5068202346
		Reduce input records=115034816
		Reduce output records=13420615
		Spilled Records=339491696
		Shuffled Maps =530
		Failed Shuffles=0
		Merged Map outputs=530
		GC time elapsed (ms)=15197
		CPU time spent (ms)=1885500
		Physical memory (bytes) snapshot=29437673472
		Virtual memory (bytes) snapshot=117218058240
		Total committed heap usage (bytes)=36874813440
	Shuffle Errors
		BAD_ID=0
		CONNECTION=0
		IO_ERROR=0
		WRONG_LENGTH=0
		WRONG_MAP=0
		WRONG_REDUCE=0
	File Input Format Counters 
		Bytes Read=3314725604
	File Output Format Counters 
		Bytes Written=2078534110
13/11/26 15:37:43 INFO streaming.StreamJob: Output directory: /user/huangxuangui/step2/out31
13/11/26 15:37:44 WARN conf.Configuration: mapred.reduce.tasks is deprecated. Instead, use mapreduce.job.reduces
packageJobJar: [/srv/hadoop/hadoop/hadoop-unjar5937470263022425812/] [] /tmp/streamjob331439374442105744.jar tmpDir=null
13/11/26 15:37:44 INFO service.AbstractService: Service:org.apache.hadoop.yarn.client.YarnClientImpl is inited.
13/11/26 15:37:44 INFO service.AbstractService: Service:org.apache.hadoop.yarn.client.YarnClientImpl is started.
13/11/26 15:37:44 INFO service.AbstractService: Service:org.apache.hadoop.yarn.client.YarnClientImpl is inited.
13/11/26 15:37:44 INFO service.AbstractService: Service:org.apache.hadoop.yarn.client.YarnClientImpl is started.
13/11/26 15:37:45 INFO mapred.FileInputFormat: Total input paths to process : 10
13/11/26 15:37:45 INFO net.NetworkTopology: Adding a new node: /default-rack/192.168.1.150:50010
13/11/26 15:37:45 INFO net.NetworkTopology: Adding a new node: /default-rack/192.168.1.200:50010
13/11/26 15:37:45 INFO mapreduce.JobSubmitter: number of splits:33
13/11/26 15:37:45 WARN conf.Configuration: mapred.jar is deprecated. Instead, use mapreduce.job.jar
13/11/26 15:37:45 WARN conf.Configuration: mapred.cache.files is deprecated. Instead, use mapreduce.job.cache.files
13/11/26 15:37:45 WARN conf.Configuration: mapred.output.value.class is deprecated. Instead, use mapreduce.job.output.value.class
13/11/26 15:37:45 WARN conf.Configuration: mapred.mapoutput.value.class is deprecated. Instead, use mapreduce.map.output.value.class
13/11/26 15:37:45 WARN conf.Configuration: mapred.used.genericoptionsparser is deprecated. Instead, use mapreduce.client.genericoptionsparser.used
13/11/26 15:37:45 WARN conf.Configuration: mapred.job.name is deprecated. Instead, use mapreduce.job.name
13/11/26 15:37:45 WARN conf.Configuration: mapred.input.dir is deprecated. Instead, use mapreduce.input.fileinputformat.inputdir
13/11/26 15:37:45 WARN conf.Configuration: mapred.output.dir is deprecated. Instead, use mapreduce.output.fileoutputformat.outputdir
13/11/26 15:37:45 WARN conf.Configuration: mapred.map.tasks is deprecated. Instead, use mapreduce.job.maps
13/11/26 15:37:45 WARN conf.Configuration: mapred.cache.files.timestamps is deprecated. Instead, use mapreduce.job.cache.files.timestamps
13/11/26 15:37:45 WARN conf.Configuration: mapred.output.key.class is deprecated. Instead, use mapreduce.job.output.key.class
13/11/26 15:37:45 WARN conf.Configuration: mapred.mapoutput.key.class is deprecated. Instead, use mapreduce.map.output.key.class
13/11/26 15:37:45 WARN conf.Configuration: mapred.working.dir is deprecated. Instead, use mapreduce.job.working.dir
13/11/26 15:37:45 INFO mapreduce.JobSubmitter: Submitting tokens for job: job_1384176415098_0186
13/11/26 15:37:45 INFO client.YarnClientImpl: Submitted application application_1384176415098_0186 to ResourceManager at workstation/192.168.1.150:8032
13/11/26 15:37:45 INFO mapreduce.Job: The url to track the job: http://workstation.mshome.net:8043/proxy/application_1384176415098_0186/
13/11/26 15:37:45 INFO mapreduce.Job: Running job: job_1384176415098_0186
13/11/26 15:37:51 INFO mapreduce.Job: Job job_1384176415098_0186 running in uber mode : false
13/11/26 15:37:51 INFO mapreduce.Job:  map 0% reduce 0%
13/11/26 15:38:05 INFO mapreduce.Job:  map 4% reduce 0%
13/11/26 15:38:06 INFO mapreduce.Job:  map 7% reduce 0%
13/11/26 15:38:08 INFO mapreduce.Job:  map 10% reduce 0%
13/11/26 15:38:09 INFO mapreduce.Job:  map 12% reduce 0%
13/11/26 15:38:11 INFO mapreduce.Job:  map 13% reduce 0%
13/11/26 15:38:12 INFO mapreduce.Job:  map 17% reduce 0%
13/11/26 15:38:15 INFO mapreduce.Job:  map 19% reduce 0%
13/11/26 15:38:16 INFO mapreduce.Job:  map 20% reduce 0%
13/11/26 15:38:19 INFO mapreduce.Job:  map 21% reduce 0%
13/11/26 15:38:21 INFO mapreduce.Job:  map 23% reduce 0%
13/11/26 15:38:26 INFO mapreduce.Job:  map 28% reduce 0%
13/11/26 15:38:29 INFO mapreduce.Job:  map 31% reduce 0%
13/11/26 15:38:30 INFO mapreduce.Job:  map 34% reduce 0%
13/11/26 15:38:33 INFO mapreduce.Job:  map 36% reduce 0%
13/11/26 15:38:36 INFO mapreduce.Job:  map 39% reduce 0%
13/11/26 15:38:39 INFO mapreduce.Job:  map 42% reduce 0%
13/11/26 15:38:42 INFO mapreduce.Job:  map 45% reduce 0%
13/11/26 15:38:45 INFO mapreduce.Job:  map 47% reduce 0%
13/11/26 15:38:48 INFO mapreduce.Job:  map 50% reduce 0%
13/11/26 15:38:51 INFO mapreduce.Job:  map 56% reduce 0%
13/11/26 15:38:54 INFO mapreduce.Job:  map 62% reduce 0%
13/11/26 15:38:55 INFO mapreduce.Job:  map 63% reduce 0%
13/11/26 15:39:17 INFO mapreduce.Job:  map 68% reduce 0%
13/11/26 15:39:18 INFO mapreduce.Job:  map 70% reduce 0%
13/11/26 15:39:20 INFO mapreduce.Job:  map 72% reduce 0%
13/11/26 15:39:24 INFO mapreduce.Job:  map 74% reduce 0%
13/11/26 15:39:26 INFO mapreduce.Job:  map 75% reduce 4%
13/11/26 15:39:27 INFO mapreduce.Job:  map 76% reduce 4%
13/11/26 15:39:28 INFO mapreduce.Job:  map 76% reduce 5%
13/11/26 15:39:29 INFO mapreduce.Job:  map 79% reduce 8%
13/11/26 15:39:31 INFO mapreduce.Job:  map 82% reduce 10%
13/11/26 15:39:32 INFO mapreduce.Job:  map 83% reduce 10%
13/11/26 15:39:33 INFO mapreduce.Job:  map 86% reduce 11%
13/11/26 15:39:34 INFO mapreduce.Job:  map 87% reduce 12%
13/11/26 15:39:35 INFO mapreduce.Job:  map 88% reduce 12%
13/11/26 15:39:37 INFO mapreduce.Job:  map 89% reduce 12%
13/11/26 15:39:38 INFO mapreduce.Job:  map 90% reduce 12%
13/11/26 15:39:40 INFO mapreduce.Job:  map 90% reduce 14%
13/11/26 15:39:42 INFO mapreduce.Job:  map 91% reduce 14%
13/11/26 15:39:43 INFO mapreduce.Job:  map 92% reduce 14%
13/11/26 15:39:45 INFO mapreduce.Job:  map 93% reduce 16%
13/11/26 15:39:46 INFO mapreduce.Job:  map 94% reduce 16%
13/11/26 15:39:49 INFO mapreduce.Job:  map 95% reduce 17%
13/11/26 15:39:50 INFO mapreduce.Job:  map 96% reduce 17%
13/11/26 15:39:53 INFO mapreduce.Job:  map 98% reduce 17%
13/11/26 15:39:54 INFO mapreduce.Job:  map 99% reduce 17%
13/11/26 15:39:55 INFO mapreduce.Job:  map 99% reduce 18%
13/11/26 15:39:56 INFO mapreduce.Job:  map 100% reduce 18%
13/11/26 15:39:57 INFO mapreduce.Job:  map 100% reduce 19%
13/11/26 15:40:01 INFO mapreduce.Job:  map 100% reduce 20%
13/11/26 15:40:06 INFO mapreduce.Job:  map 100% reduce 21%
13/11/26 15:40:15 INFO mapreduce.Job:  map 100% reduce 22%
13/11/26 15:40:24 INFO mapreduce.Job:  map 100% reduce 23%
13/11/26 15:40:32 INFO mapreduce.Job:  map 100% reduce 24%
13/11/26 15:40:40 INFO mapreduce.Job:  map 100% reduce 25%
13/11/26 15:40:46 INFO mapreduce.Job:  map 100% reduce 26%
13/11/26 15:40:48 INFO mapreduce.Job:  map 100% reduce 28%
13/11/26 15:40:49 INFO mapreduce.Job:  map 100% reduce 30%
13/11/26 15:40:51 INFO mapreduce.Job:  map 100% reduce 31%
13/11/26 15:40:52 INFO mapreduce.Job:  map 100% reduce 34%
13/11/26 15:40:54 INFO mapreduce.Job:  map 100% reduce 36%
13/11/26 15:40:55 INFO mapreduce.Job:  map 100% reduce 37%
13/11/26 15:40:57 INFO mapreduce.Job:  map 100% reduce 38%
13/11/26 15:41:00 INFO mapreduce.Job:  map 100% reduce 39%
13/11/26 15:41:03 INFO mapreduce.Job:  map 100% reduce 41%
13/11/26 15:41:10 INFO mapreduce.Job:  map 100% reduce 42%
13/11/26 15:41:19 INFO mapreduce.Job:  map 100% reduce 43%
13/11/26 15:41:32 INFO mapreduce.Job:  map 100% reduce 44%
13/11/26 15:41:46 INFO mapreduce.Job:  map 100% reduce 45%
13/11/26 15:41:55 INFO mapreduce.Job:  map 100% reduce 46%
13/11/26 15:42:03 INFO mapreduce.Job:  map 100% reduce 47%
13/11/26 15:42:13 INFO mapreduce.Job:  map 100% reduce 48%
13/11/26 15:42:26 INFO mapreduce.Job:  map 100% reduce 49%
13/11/26 15:42:39 INFO mapreduce.Job:  map 100% reduce 50%
13/11/26 15:42:51 INFO mapreduce.Job:  map 100% reduce 51%
13/11/26 15:43:03 INFO mapreduce.Job:  map 100% reduce 52%
13/11/26 15:43:09 INFO mapreduce.Job:  map 100% reduce 53%
13/11/26 15:43:12 INFO mapreduce.Job:  map 100% reduce 54%
13/11/26 15:43:14 INFO mapreduce.Job:  map 100% reduce 55%
13/11/26 15:43:15 INFO mapreduce.Job:  map 100% reduce 57%
13/11/26 15:43:18 INFO mapreduce.Job:  map 100% reduce 59%
13/11/26 15:43:21 INFO mapreduce.Job:  map 100% reduce 61%
13/11/26 15:43:24 INFO mapreduce.Job:  map 100% reduce 63%
13/11/26 15:43:26 INFO mapreduce.Job:  map 100% reduce 64%
13/11/26 15:43:27 INFO mapreduce.Job:  map 100% reduce 65%
13/11/26 15:43:30 INFO mapreduce.Job:  map 100% reduce 67%
13/11/26 15:43:33 INFO mapreduce.Job:  map 100% reduce 70%
13/11/26 15:43:36 INFO mapreduce.Job:  map 100% reduce 72%
13/11/26 15:43:39 INFO mapreduce.Job:  map 100% reduce 74%
13/11/26 15:43:40 INFO mapreduce.Job:  map 100% reduce 75%
13/11/26 15:43:49 INFO mapreduce.Job:  map 100% reduce 77%
13/11/26 15:43:52 INFO mapreduce.Job:  map 100% reduce 79%
13/11/26 15:43:55 INFO mapreduce.Job:  map 100% reduce 80%
13/11/26 15:44:01 INFO mapreduce.Job:  map 100% reduce 81%
13/11/26 15:44:04 INFO mapreduce.Job:  map 100% reduce 82%
13/11/26 15:44:07 INFO mapreduce.Job:  map 100% reduce 83%
13/11/26 15:44:10 INFO mapreduce.Job:  map 100% reduce 84%
13/11/26 15:44:17 INFO mapreduce.Job:  map 100% reduce 85%
13/11/26 15:44:23 INFO mapreduce.Job:  map 100% reduce 86%
13/11/26 15:44:31 INFO mapreduce.Job:  map 100% reduce 87%
13/11/26 15:44:43 INFO mapreduce.Job:  map 100% reduce 88%
13/11/26 15:44:53 INFO mapreduce.Job:  map 100% reduce 89%
13/11/26 15:45:02 INFO mapreduce.Job:  map 100% reduce 90%
13/11/26 15:45:11 INFO mapreduce.Job:  map 100% reduce 91%
13/11/26 15:45:20 INFO mapreduce.Job:  map 100% reduce 92%
13/11/26 15:45:29 INFO mapreduce.Job:  map 100% reduce 93%
13/11/26 15:45:38 INFO mapreduce.Job:  map 100% reduce 94%
13/11/26 15:45:47 INFO mapreduce.Job:  map 100% reduce 95%
13/11/26 15:45:56 INFO mapreduce.Job:  map 100% reduce 96%
13/11/26 15:46:05 INFO mapreduce.Job:  map 100% reduce 97%
13/11/26 15:46:14 INFO mapreduce.Job:  map 100% reduce 98%
13/11/26 15:46:23 INFO mapreduce.Job:  map 100% reduce 99%
13/11/26 15:46:35 INFO mapreduce.Job:  map 100% reduce 100%
13/11/26 15:46:42 INFO mapreduce.Job: Job job_1384176415098_0186 completed successfully
13/11/26 15:46:42 INFO mapreduce.Job: Counters: 44
	File System Counters
		FILE: Number of bytes read=12398239665
		FILE: Number of bytes written=18626106016
		FILE: Number of read operations=0
		FILE: Number of large read operations=0
		FILE: Number of write operations=0
		HDFS: Number of bytes read=2078836979
		HDFS: Number of bytes written=3256625824
		HDFS: Number of read operations=129
		HDFS: Number of large read operations=0
		HDFS: Number of write operations=20
	Job Counters 
		Killed map tasks=1
		Launched map tasks=34
		Launched reduce tasks=10
		Rack-local map tasks=34
		Total time spent by all maps in occupied slots (ms)=4293474
		Total time spent by all reduces in occupied slots (ms)=11252886
	Map-Reduce Framework
		Map input records=13420615
		Map output records=115034816
		Map output bytes=5996311585
		Map output materialized bytes=6226415510
		Input split bytes=3861
		Combine input records=0
		Combine output records=0
		Reduce input groups=13420615
		Reduce shuffle bytes=6226415510
		Reduce input records=115034816
		Reduce output records=13420615
		Spilled Records=343953277
		Shuffled Maps =330
		Failed Shuffles=0
		Merged Map outputs=330
		GC time elapsed (ms)=20166
		CPU time spent (ms)=2496370
		Physical memory (bytes) snapshot=25399619584
		Virtual memory (bytes) snapshot=85397336064
		Total committed heap usage (bytes)=31320571904
	Shuffle Errors
		BAD_ID=0
		CONNECTION=0
		IO_ERROR=0
		WRONG_LENGTH=0
		WRONG_MAP=0
		WRONG_REDUCE=0
	File Input Format Counters 
		Bytes Read=2078833118
	File Output Format Counters 
		Bytes Written=3256625824
13/11/26 15:46:42 INFO streaming.StreamJob: Output directory: /user/huangxuangui/step2/out40
packageJobJar: [/srv/hadoop/hadoop/hadoop-unjar2079781465145277808/] [] /tmp/streamjob227526720853801052.jar tmpDir=null
13/11/26 15:46:43 INFO service.AbstractService: Service:org.apache.hadoop.yarn.client.YarnClientImpl is inited.
13/11/26 15:46:43 INFO service.AbstractService: Service:org.apache.hadoop.yarn.client.YarnClientImpl is started.
13/11/26 15:46:43 INFO service.AbstractService: Service:org.apache.hadoop.yarn.client.YarnClientImpl is inited.
13/11/26 15:46:43 INFO service.AbstractService: Service:org.apache.hadoop.yarn.client.YarnClientImpl is started.
13/11/26 15:46:44 INFO mapred.FileInputFormat: Total input paths to process : 10
13/11/26 15:46:44 INFO net.NetworkTopology: Adding a new node: /default-rack/192.168.1.150:50010
13/11/26 15:46:44 INFO net.NetworkTopology: Adding a new node: /default-rack/192.168.1.200:50010
13/11/26 15:46:44 INFO mapreduce.JobSubmitter: number of splits:53
13/11/26 15:46:44 WARN conf.Configuration: mapred.jar is deprecated. Instead, use mapreduce.job.jar
13/11/26 15:46:44 WARN conf.Configuration: mapred.cache.files is deprecated. Instead, use mapreduce.job.cache.files
13/11/26 15:46:44 WARN conf.Configuration: mapred.output.value.class is deprecated. Instead, use mapreduce.job.output.value.class
13/11/26 15:46:44 WARN conf.Configuration: mapred.mapoutput.value.class is deprecated. Instead, use mapreduce.map.output.value.class
13/11/26 15:46:44 WARN conf.Configuration: mapred.used.genericoptionsparser is deprecated. Instead, use mapreduce.client.genericoptionsparser.used
13/11/26 15:46:44 WARN conf.Configuration: mapred.job.name is deprecated. Instead, use mapreduce.job.name
13/11/26 15:46:44 WARN conf.Configuration: mapred.input.dir is deprecated. Instead, use mapreduce.input.fileinputformat.inputdir
13/11/26 15:46:44 WARN conf.Configuration: mapred.output.dir is deprecated. Instead, use mapreduce.output.fileoutputformat.outputdir
13/11/26 15:46:44 WARN conf.Configuration: mapred.map.tasks is deprecated. Instead, use mapreduce.job.maps
13/11/26 15:46:44 WARN conf.Configuration: mapred.cache.files.timestamps is deprecated. Instead, use mapreduce.job.cache.files.timestamps
13/11/26 15:46:44 WARN conf.Configuration: mapred.output.key.class is deprecated. Instead, use mapreduce.job.output.key.class
13/11/26 15:46:44 WARN conf.Configuration: mapred.mapoutput.key.class is deprecated. Instead, use mapreduce.map.output.key.class
13/11/26 15:46:44 WARN conf.Configuration: mapred.working.dir is deprecated. Instead, use mapreduce.job.working.dir
13/11/26 15:46:44 INFO mapreduce.JobSubmitter: Submitting tokens for job: job_1384176415098_0189
13/11/26 15:46:44 INFO client.YarnClientImpl: Submitted application application_1384176415098_0189 to ResourceManager at workstation/192.168.1.150:8032
13/11/26 15:46:44 INFO mapreduce.Job: The url to track the job: http://workstation.mshome.net:8043/proxy/application_1384176415098_0189/
13/11/26 15:46:44 INFO mapreduce.Job: Running job: job_1384176415098_0189
13/11/26 15:46:50 INFO mapreduce.Job: Job job_1384176415098_0189 running in uber mode : false
13/11/26 15:46:50 INFO mapreduce.Job:  map 0% reduce 0%
13/11/26 15:47:02 INFO mapreduce.Job:  map 2% reduce 0%
13/11/26 15:47:03 INFO mapreduce.Job:  map 13% reduce 0%
13/11/26 15:47:04 INFO mapreduce.Job:  map 24% reduce 0%
13/11/26 15:47:05 INFO mapreduce.Job:  map 32% reduce 0%
13/11/26 15:47:06 INFO mapreduce.Job:  map 36% reduce 0%
13/11/26 15:47:07 INFO mapreduce.Job:  map 38% reduce 0%
13/11/26 15:47:13 INFO mapreduce.Job:  map 40% reduce 0%
13/11/26 15:47:14 INFO mapreduce.Job:  map 44% reduce 0%
13/11/26 15:47:15 INFO mapreduce.Job:  map 48% reduce 0%
13/11/26 15:47:16 INFO mapreduce.Job:  map 51% reduce 11%
13/11/26 15:47:17 INFO mapreduce.Job:  map 53% reduce 11%
13/11/26 15:47:18 INFO mapreduce.Job:  map 62% reduce 11%
13/11/26 15:47:19 INFO mapreduce.Job:  map 65% reduce 14%
13/11/26 15:47:20 INFO mapreduce.Job:  map 69% reduce 14%
13/11/26 15:47:21 INFO mapreduce.Job:  map 72% reduce 14%
13/11/26 15:47:22 INFO mapreduce.Job:  map 72% reduce 17%
13/11/26 15:47:24 INFO mapreduce.Job:  map 77% reduce 17%
13/11/26 15:47:25 INFO mapreduce.Job:  map 83% reduce 19%
13/11/26 15:47:26 INFO mapreduce.Job:  map 84% reduce 19%
13/11/26 15:47:27 INFO mapreduce.Job:  map 90% reduce 19%
13/11/26 15:47:28 INFO mapreduce.Job:  map 100% reduce 24%
13/11/26 15:47:32 INFO mapreduce.Job:  map 100% reduce 26%
13/11/26 15:47:34 INFO mapreduce.Job:  map 100% reduce 27%
13/11/26 15:47:37 INFO mapreduce.Job:  map 100% reduce 30%
13/11/26 15:47:40 INFO mapreduce.Job:  map 100% reduce 32%
13/11/26 15:47:43 INFO mapreduce.Job:  map 100% reduce 37%
13/11/26 15:47:46 INFO mapreduce.Job:  map 100% reduce 50%
13/11/26 15:47:49 INFO mapreduce.Job:  map 100% reduce 62%
13/11/26 15:47:52 INFO mapreduce.Job:  map 100% reduce 68%
13/11/26 15:47:55 INFO mapreduce.Job:  map 100% reduce 69%
13/11/26 15:47:58 INFO mapreduce.Job:  map 100% reduce 71%
13/11/26 15:48:01 INFO mapreduce.Job:  map 100% reduce 73%
13/11/26 15:48:04 INFO mapreduce.Job:  map 100% reduce 75%
13/11/26 15:48:16 INFO mapreduce.Job:  map 100% reduce 82%
13/11/26 15:48:19 INFO mapreduce.Job:  map 100% reduce 84%
13/11/26 15:48:22 INFO mapreduce.Job:  map 100% reduce 86%
13/11/26 15:48:25 INFO mapreduce.Job:  map 100% reduce 88%
13/11/26 15:48:28 INFO mapreduce.Job:  map 100% reduce 90%
13/11/26 15:48:31 INFO mapreduce.Job:  map 100% reduce 92%
13/11/26 15:48:34 INFO mapreduce.Job:  map 100% reduce 93%
13/11/26 15:48:37 INFO mapreduce.Job:  map 100% reduce 95%
13/11/26 15:48:40 INFO mapreduce.Job:  map 100% reduce 97%
13/11/26 15:48:44 INFO mapreduce.Job:  map 100% reduce 99%
13/11/26 15:48:45 INFO mapreduce.Job:  map 100% reduce 100%
13/11/26 15:48:45 INFO mapreduce.Job: Job job_1384176415098_0189 completed successfully
13/11/26 15:48:45 INFO mapreduce.Job: Counters: 43
	File System Counters
		FILE: Number of bytes read=602539897
		FILE: Number of bytes written=1209224468
		FILE: Number of read operations=0
		FILE: Number of large read operations=0
		FILE: Number of write operations=0
		HDFS: Number of bytes read=3314733785
		HDFS: Number of bytes written=414672978
		HDFS: Number of read operations=162
		HDFS: Number of large read operations=0
		HDFS: Number of write operations=2
	Job Counters 
		Launched map tasks=53
		Launched reduce tasks=1
		Rack-local map tasks=53
		Total time spent by all maps in occupied slots (ms)=1198098
		Total time spent by all reduces in occupied slots (ms)=300030
	Map-Reduce Framework
		Map input records=13420615
		Map output records=13420615
		Map output bytes=575692443
		Map output materialized bytes=602540209
		Input split bytes=6201
		Combine input records=0
		Combine output records=0
		Reduce input groups=1358417
		Reduce shuffle bytes=602540209
		Reduce input records=13420615
		Reduce output records=13420615
		Spilled Records=26841230
		Shuffled Maps =53
		Failed Shuffles=0
		Merged Map outputs=53
		GC time elapsed (ms)=5092
		CPU time spent (ms)=351950
		Physical memory (bytes) snapshot=17475112960
		Virtual memory (bytes) snapshot=87839592448
		Total committed heap usage (bytes)=22134390784
	Shuffle Errors
		BAD_ID=0
		CONNECTION=0
		IO_ERROR=0
		WRONG_LENGTH=0
		WRONG_MAP=0
		WRONG_REDUCE=0
	File Input Format Counters 
		Bytes Read=3314727584
	File Output Format Counters 
		Bytes Written=414672978
13/11/26 15:48:45 INFO streaming.StreamJob: Output directory: /user/huangxuangui/out

```