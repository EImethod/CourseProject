<html>

<!-- ����һ��ע��! head��������ı�ǩ����,��������ҳ��������ʾ -->
<head>
<title>ZJUT ACM</title>

<style type="text/css">
	h1 {color:red}
	p {color:blue}
</style>

</head>

<body>
<center>
<h1>ZJUT ACM OnlineJudge <sub>tm</sub> <sup> top</sup></h1>
</center>

<hr align="center" width="80%" color="red"> <!-- һ������ -->

<a href="mysqlTest.php">mysqlTest</a> <br>
<a href="javascriptTest.php">javascriptTest</a> <br>

<center>
<form action="login.php" method="post">
	<input type="text" name="username" value="dd">
	<input type="password" name="userpass" value="123456">
	<input type="submit" value="login">
</form>  </center>

<a href="frameTest.php">frameTest</a>


<pre>   Ԥ���ʽ���pre,    ����
                 ������֮���ǿ��Ե�Ŷ,��������!!
</pre>

<?php
/*
	$pipe=fopen("\\\\.\\pipe\\samplenamedpipe", "w");
	if( !$pipe ){
		die("die");
	}
	fwrite($pipe, "hello kitty!!");
	fclose($pipe);
	*/
	$pipe=fopen("\\\\.\\pipe\\samplenamedpipe", "r");
	if( !$pipe ){
		die("die");
	}
	fgets($pipe,$response);
	echo $response."<br>";
	fclose($pipe);

	//$t=@shell_exec("D:/Notepad++/BC9.exe");
	//echo $t."  ffffffffffffffffff<br>";
	
echo 'Today is '.date("Y-m-d");
echo "<br />";
//$tomorrow=mktime(0,0,0,date("m"),date("d")+1,date("Y"));
$tomorrow = mktime(0,0,0,date("m"),date("d")+1,date("Y"));
echo "Tomorrow is ".date("Y-m-d",$tomorrow);
echo "<br><br><br><br>"
?>

<center><a href="acmTemp/dinic.txt">�����dinicģ��</a></center>
<a href="picture/picIndex.html"> ����ͼƬ</a>

<br>
<br>

<center>
<p style="color: #800">�����ϴ�һ���ļ�,С��20MŶ</p>
</center>

<form action="upload_file.php" method="post"
	enctype="multipart/form-data"><label for="file">Filename:</label> <input
	type="file" name="userfile" id="file" /> <input type="submit" name="submit"
	value="����ϴ��ļ�" /></form>

<form action="mailto:zjut_DD@163.com" method="post">name: <input
	type="text" name="name"> <input type="submit" value="ddd"></form>

<br>
where are come from?
<select name="where">
<option value="HK">HongKong</option>
<option value="USA">United States</option>
<option value="RU">Russia</option>
</select> <br>

<br>
<br>
Give your comments:<br>
<textarea name="comments" rows="4" cols="40"></textarea>
<br>
<?php include("hello1000.php");?>


<marquee  behavior=alternate>ײ��ײȥ�������һ���</marquee>




ע�����¼���:<br>
<ol> <!-- ordered list �����б�-->
<li>��Ҫ�ٵ�</li>  <!-- list item �б���-->
<li>��Ҫ����</li>
<li>��Ҫ˵��</li>
</ol>

ע�����¼���:<br>
<ul> <!-- unordered list �����б�-->
<li>��Ҫ�ٵ�</li> 
<li>��Ҫ����</li>
<li>��Ҫ˵��</li>
</ul>
<br>



<b>����Ӵ�</b>  <!-- bold -->
<i>б����</i>  <!-- inclined��б�� -->
<u>�»���</u>  <!-- underline -->
<strike>ɾ����</strike>

<table width="60%" border="2" align="center">
	<tr align="center" bgcolor="red">
		<td>(1,1)</td>
		<td>(1,2)</td>
	</tr>
	<tr bgcolor="white">
		<td><b><strike>(2,1)</strike></b></td>
		<td bgcolor="gray">(2,2)</td>
	</tr>
	<tr bgcolor="yellow">
		<td>(3,1)</td>
		<td>(3,2)</td>
	</tr>
</table>

<img alt="this is daodao's head portrait" src="upload/gg.jpg" width=120 height=120>

<pre>
struct LinkedList{
	struct Node{ T val; Node *p, *x, *ps, *xs; }dd[MAXN],*head; //pre next  pre_seg  next_seg
	int e, size;
	LinkedList(){ clear(); }
	void clear(){ size=e=0; }
};
int main(){
	printf("hello world!\n";
}
</pre>

</body>
</html>
