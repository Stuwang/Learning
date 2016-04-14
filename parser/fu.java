package suanfu;

import java.util.Vector;

public class fu {
	public char left;
	public String right;
	public String ends;
	public fu(char ch,String str){
		left = ch;
		right = str;
	}
}

class firstvt{
	public char ch;
	Vector<Character> s = new Vector<Character>();
}

class lastvt{
	public char ch;
	Vector<Character> s = new Vector<Character>();
}

class chs{
	public char Upper;
	public char Lower;
	public chs(char a,char b){
		Upper = a;
		Lower = b;
	}
}
