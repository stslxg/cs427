cd /home/huangxuangui/hw3/step2
/srv/hadoop/bin/hadoop jar /srv/hadoop/share/hadoop/tools/lib/hadoop-streaming-2.0.5-alpha.jar \
    -files "mapper.py,reducer.py" \
    -mapper "mapper.py" \
    -reducer "reducer.py" \
    -input /user/huangxuangui/step1/out \
    -output /user/huangxuangui/step2/out00
#/srv/hadoop/bin/hdfs dfs -get /user/huangxuangui/step2/out00 /home/huangxuangui/hw3/step2/out00
for i in {1..4}
do
/srv/hadoop/bin/hadoop jar /srv/hadoop/share/hadoop/tools/lib/hadoop-streaming-2.0.5-alpha.jar \
    -files "mapper2.py,reducer2.py" \
    -mapper "mapper2.py" \
    -reducer "reducer2.py" \
    -input "/user/huangxuangui/step2/out$(($i-1))0" \
    -output "/user/huangxuangui/step2/out$(($i-1))1"
#/srv/hadoop/bin/hdfs dfs -get /user/huangxuangui/step2/out01 /home/huangxuangui/hw3/step2/out01
/srv/hadoop/bin/hadoop jar /srv/hadoop/share/hadoop/tools/lib/hadoop-streaming-2.0.5-alpha.jar \
    -files "mapper.py,reducer.py" \
    -mapper "mapper.py" \
    -reducer "reducer.py" \
    -input "/user/huangxuangui/step2/out$(($i-1))1" \
    -output "/user/huangxuangui/step2/out${i}0"
done
#/srv/hadoop/bin/hdfs dfs -get /user/huangxuangui/step2/out51 /home/huangxuangui/hw3/step2/out51
