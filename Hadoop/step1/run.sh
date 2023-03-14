cd /home/huangxuangui/hw3/step1
/srv/hadoop/bin/hadoop jar /srv/hadoop/share/hadoop/tools/lib/hadoop-streaming-2.0.5-alpha.jar \
    -D mapred.reduce.tasks=6 \
    -files "mapper.py" \
    -mapper "mapper.py" \
    -input /user/huangxuangui/in \
    -output /user/huangxuangui/step1/out
