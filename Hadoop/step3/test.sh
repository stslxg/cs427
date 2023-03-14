cd /home/huangxuangui/hw3/step3
/srv/hadoop/bin/hadoop jar /srv/hadoop/share/hadoop/tools/lib/hadoop-streaming-2.0.5-alpha.jar \
    -files "mapper.py,reducer.py" \
    -mapper "mapper.py" \
    -reducer "reducer.py" \
    -input /user/huangxuangui/step2/out40 \
    -output /user/huangxuangui/out
/srv/hadoop/bin/hdfs dfs -get /user/huangxuangui/out /home/huangxuangui/hw3/out
