for i in {0..4}
do
/srv/hadoop/bin/hdfs dfs -rm -r "/user/huangxuangui/step2/out${i}0"
rm -rf "/home/huangxuangui/hw3/step2/out${i}0"
/srv/hadoop/bin/hdfs dfs -rm -r "/user/huangxuangui/step2/out${i}1"
rm -rf "/home/huangxuangui/hw3/step2/out${i}1"
done