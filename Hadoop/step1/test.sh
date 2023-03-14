cd /home/huangxuangui/hw3/step1
/srv/hadoop/bin/hadoop jar /srv/hadoop/share/hadoop/tools/lib/hadoop-streaming-2.0.5-alpha.jar \
    -files "mapper.py" \
    -mapper "mapper.py" \
    -input /user/huangxuangui/in/wiki_0.txt \
    -output /user/huangxuangui/step1/out
/srv/hadoop/bin/hdfs dfs -get /user/huangxuangui/step1/out /home/huangxuangui/hw3/step1/out