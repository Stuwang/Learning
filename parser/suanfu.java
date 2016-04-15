import java.util.Stack;
import java.util.Vector;

public class suanfu {

	public String in;
	public Vector<fu> fus;
	Vector<Character> starts;
	Vector<Character> ends;
	boolean[][] firstvts;
	boolean[][] lastvts;
	int[][] youxian;
	
	/**
	 * 测试案例1
	 */
	public void testInit1(){
		fus.add(new fu('E',"E+T" ));
		fus.add(new fu('E',"T" ));
		fus.add(new fu('T',"T*F" ));
		fus.add(new fu('T',"F" ));
		fus.add(new fu('F',"P^F" ));
		fus.add(new fu('F',"P" ));
		fus.add(new fu('P',"(E)" ));
		fus.add(new fu('P',"i" ));
		fus.add(new fu(' ',"#E#" ));
		this.in = "i+i*(i)+(i+i)^i";
	}
	
	/**
	 * 测试案例2
	 */
	public void testInit2(){
		fus.add(new fu('S',"bAb" ));
		fus.add(new fu('A',"(B" ));
		fus.add(new fu('A',"a" ));
		fus.add(new fu('B',"Aa)" ));
		fus.add(new fu('E',"#S#" ));
		this.in = "b((aa))b";
	}
	
	/**
	 * 初始化  让用户输入
	 */
	public void init(){
		fus = new Vector<fu>();
		/**
		 * 插入初始化输入代码
		 */
		
		testInit1();
		
		
		for(fu i:fus){
			String str = i.right;
			String rn = "";
			for(int m = 0;m < str.length();m++){
				if(Character.isUpperCase( str.charAt(m) )){
					rn = rn +'N';
				}else{
					rn = rn + str.charAt(m);
				}
			}
			i.ends = rn;
		}
	}
	
	/**
	 * 非终结符初始化
	 */
	public void getStarts(){
		Vector<Character> re = new Vector<Character>();
		for(fu i:fus){
			if( !re.contains(i.left) )
				re.add(i.left);
		}
		starts = re;
	}
	
	/**
	 * 终结符初始化
	 */
	public void getEnds(){
		Vector<Character> re = new Vector<Character>();
		for(fu m:fus){
			String str =  m.right;
			for(int i = 0; i < str.length();i++)
			if( !re.contains(str.charAt(i)) 
					&& !Character.isUpperCase(str.charAt(i)) )
				re.add(str.charAt(i));
		}
		ends =  re;
	}
	
	
	public int getStart(char ch){
		return starts.indexOf(ch);
	}
	
	public int getEnd(char ch){
		return ends.indexOf(ch);
	}
	
	/**
	 * firstvt 初始化
	 */
	public void firstvts(){
		boolean[][] re = new boolean[starts.size()][ends.size()]; 
		firstvts =  re;
		Stack<chs> sta = new Stack<chs>();
		for(int i=0;i<starts.size();i++)
			for(int j=0;j<ends.size();j++)
				re[i][j] = false;
		for(fu i:fus){
			String str = i.right;
			if(!Character.isUpperCase(str.charAt(0))){
				re[getStart(i.left)][getEnd(str.charAt(0))] = true;
				chs aChs =new chs(i.left, str.charAt(0));
				if(!sta.contains(aChs))
					sta.push(aChs);
			}else if( 	str.length() >=2 && 
						!Character.isUpperCase(str.charAt(1)) &&
						Character.isUpperCase(str.charAt(0))
					){
				re[getStart(i.left)][getEnd(str.charAt(1))] = true;
				chs aChs =new chs(i.left, str.charAt(1));
				if(!sta.contains(aChs))
					sta.push(aChs);
			}
		}
		
		
		/*
		 * 测试
		 
		for(int i = 0;i< firstvts.length;i++){
			for(int j = 0;j< firstvts[i].length;j++){
				System.out.print(firstvts[i][j]+" ");
			}
			System.out.println();
		}
		*/
		
		for(;!sta.empty();){
			chs tmp = sta.pop();
			for(fu i:fus){
				int m = getStart(i.left);
				int n = getEnd(tmp.Lower);
				if(firstvts[m][n] == false && i.right.charAt(0) == tmp.Upper ){
					firstvts[m][n] = true;
					sta.push(new chs( i.left,tmp.Lower) );
				}
			}
		}		
	}
	
	/**
	 * lastvt 初始化
	 */
	public void lastvts(){
		boolean[][] re = new boolean[starts.size()][ends.size()]; 
		lastvts =  re;
		Stack<chs> sta = new Stack<chs>();
		for(int i=0;i<starts.size();i++)
			for(int j=0;j<ends.size();j++)
				re[i][j] = false;
		for(fu i:fus){
			String str = i.right;
			if(!Character.isUpperCase(str.charAt(str.length()-1))){
				re[getStart(i.left)][getEnd(str.charAt(str.length()-1))] = true;
				chs aChs =new chs(i.left, str.charAt(str.length()-1));
				if(!sta.contains(aChs))
					sta.push(aChs);
			}else if( 	str.length() >=2 && 
						!Character.isUpperCase(str.charAt(str.length()-2)) &&
						Character.isUpperCase(str.charAt(str.length()-1))
					){
				re[getStart(i.left)][getEnd(str.charAt(str.length()-2))] = true;
				chs aChs =new chs(i.left, str.charAt(str.length()-2));
				if(!sta.contains(aChs))
					sta.push(aChs);
			}
		}
		
		
		/*
		 * 测试
		
		System.out.printf("%5s","");
		for(int i=0;i<ends.size();i++){
			System.out.printf("%7s",  ends.get(i));
		}
		System.out.println();
		for(int i = 0;i< lastvts.length;i++){
			System.out.printf("%5s", starts.get(i));
			for(int j = 0;j<  lastvts[i].length;j++){
				System.out.printf("%7s", lastvts[i][j]);
			}
			System.out.println();
		}
		for(chs i:sta){
			System.out.println(i.Upper+" "+i.Lower);
		}
		*/
		
		for(;!sta.empty();){
			chs tmp = sta.pop();
			for(fu i:fus){
				int m = getStart(i.left);
				int n = getEnd(tmp.Lower);
				if(lastvts[m][n] == false && i.right.charAt(i.right.length()-1) == tmp.Upper ){
					lastvts[m][n] = true;
					sta.push(new chs( i.left,tmp.Lower) );
				}
			}
		}
		
		
	}
	
	/**
	 * 优先关系表初始化
	 * @return
	 */
	public int initYouxian(){
		youxian = new int[ends.size()][ends.size()];
		//System.out.println("终结符数量："+ends.size());
		for(int i=0;i<ends.size();i++){
			//System.out.print(i+":");
			for(int j=0;j<ends.size();j++){
				//System.out.print(" "+j);
				//System.out.println();
				youxian[i][j] = -2;
			}
		}
		for(fu i:fus){
			String m = i.right;
			for(int j=0;j<m.length() -1;j++){
				
				if(!Character.isUpperCase(m.charAt(j)) &&
						!Character.isUpperCase(m.charAt(j+1)) ){
					if(youxian[ getEnd(m.charAt(j)) ][getEnd(m.charAt(j+1))] == -2
							|| youxian[ getEnd(m.charAt(j)) ][getEnd(m.charAt(j+1))] == 0){
						youxian[ getEnd(m.charAt(j)) ][getEnd(m.charAt(j+1))] =0;
					}else{
						return -1;
					}
					
				}
				 
				if(		j < m.length()-2 &&
						!Character.isUpperCase(m.charAt(j)) &&
						!Character.isUpperCase(m.charAt(j+2)) &&
						Character.isUpperCase(m.charAt(j+1)) 
						){
					if(youxian[getEnd(m.charAt(j)) ][getEnd(m.charAt(j+2))] == -2
							|| youxian[getEnd(m.charAt(j)) ][getEnd(m.charAt(j+2))] == 0){
						youxian[ getEnd(m.charAt(j)) ][getEnd(m.charAt(j+2))] =0;
					}else{
						return -1;
					}
				}
				if(	!Character.isUpperCase(m.charAt(j)) &&
						Character.isUpperCase(m.charAt(j+1))
						){
					boolean[] ends_ = firstvts[getStart(m.charAt(j+1))];
					for(int tm = 0;tm < ends_.length ; tm ++){
						if(ends_[tm] == true){
							if(youxian[getEnd(m.charAt(j))][tm] == -2 ||
									youxian[getEnd(m.charAt(j))][tm] == -1){
								youxian[getEnd(m.charAt(j))][tm] = -1;
							}else{
								return -1;
							}
						}
					}
				}
				
				if(	!Character.isUpperCase(m.charAt(j+1)) &&
						Character.isUpperCase(m.charAt(j))
						){
					boolean[] ends_ = lastvts[getStart(m.charAt(j))];
					for(int tm = 0;tm < ends_.length ; tm ++){
						if(ends_[tm] == true){
							if(youxian[tm][getEnd(m.charAt(j+1))] == -2 ||
									youxian[tm][getEnd(m.charAt(j+1))] == 1){
								youxian[tm][getEnd(m.charAt(j+1))] = 1;
							}else{
								return -1;
							}
							
						}
					}
				}
			}
		}
		return 1;
	}
	
	/**
	 * 句柄的非终结符提取串
	 * @param str 句柄
	 * @return
	 */
	public String getE(String str){
		String re="";
		for(int i=0;i<str.length();i++){
			if(Character.isUpperCase(str.charAt(i))){
				re = re + "N";
			}else{
				re = re + str.charAt(i);
			}
				
		}
		return re;
	}
	
	/**
	 * 获取  句柄的非终结符提取串   所对应的左部
	 * @param str 句柄的非终结符提取串
	 * @return
	 */
	public char getLeft(String str){
		char ch = '_';
		for(fu i:fus){
			if(i.ends.equals(str)){
				ch = i.left; 
			}
		}
		return ch;
	}
	
	/**
	 * 判断 a？b 的优先关系
	 * @param a
	 * @param b
	 * @return
	 */
	public int cout(char a,char b){
		return youxian[getEnd(a)][getEnd(b)];
	}
	
	/**
	 * 分析
	 */
	public void anylize(){
		StringBuffer any = new StringBuffer(); 
		int k = 0,cout = 0;
		int mark = 0;
		any.append('#');
		String in = this.in+"#";
		
 		System.out.printf("%-20s%5s%20s%20s\n","stack","char","least","nextstep");
		for(;;){
			System.out.printf("%-20s%5s%20s",any,in.charAt(cout),in.substring(cout, in.length()));
			int j;
			char ch = in.charAt(cout);
			
			if(!Character.isUpperCase(any.charAt(k))){
				j = k;
			}else{
				j = k-1;
			}
			
			char q;
			if(cout(any.charAt(j),ch)==1){
				do{
					q = any.charAt(j);
					if(!Character.isUpperCase(any.charAt(j-1))){
						j = j-1;
					}else{
						j = j-2;
					}
				}while(cout(any.charAt(j),q) >= 0);
				/**
				 * 规约 暂时还没有写
				 */
				String tr_tm = any.substring(j+1, any.length());
				char left = getLeft(getE(tr_tm));
				if(left=='_'){
					mark = -1;
					System.out.println("出错1");
					System.out.println(getE(tr_tm)+"无法规约");
					break;
				}
				String tm_ = ""+left;
				any.replace(j+1, any.length(), tm_);
				k = j+1;
				System.out.printf("%20s\n",tr_tm+":"+getE(tr_tm)+"规约为"+getLeft(getE(tr_tm)) );
			
				
			}else if(cout(any.charAt(j),ch)==-1){
				k++;
				any.append(ch);
				System.out.printf("%20s\n","移入"+ch);
				cout++;
				
			}else if(cout(any.charAt(j),ch)==0){
				if(any.charAt(j)=='#'){
					if(any.length() == 2 && ch == '#'){
						mark = 1;
						System.out.println("test-正常结束");
						break;
					}else{
						mark = -1;
						System.out.println("出错1");
						break;
					}
				}else{
					k++;
					any.append(ch);
					System.out.printf("%20s\n","移入"+ch);
					cout++;
				}
			}else{
				//三种都不满足，出错了
				mark = -1;
				//System.out.println(any+":"+in.substring(cout-1, in.length()));
				System.out.printf("%20s\n","test-出错2");
				break;
			}
		}
		if(mark == -1){
			System.out.println("规约出错！");
		}else if(mark == 1){
			System.out.println("规约完成!");
		}
	}
	
	/**
	 * 输出所有的非终结符
	 */
	public void printStarts(){
		for(char i:starts){
			System.out.print(i+" ");
		}
		System.out.println();
	}
	
	/**
	 * 输出所有终结符
	 */
	public void printEnds(){
		for(char i:ends){
			System.out.print(i+" ");
		}
		System.out.println();
	}
	
	/**
	 * 输出非终结符的firstvt集合
	 */
	public void printFirstvts(){
		System.out.printf("%5s","");
		for(int i=0;i<ends.size();i++){
			System.out.printf("%7s", ends.get(i));
		}
		System.out.println();
		for(int i = 0;i< firstvts.length;i++){
			System.out.printf("%5s",starts.get(i));
			for(int j = 0;j< firstvts[i].length;j++){
				System.out.printf("%7s",firstvts[i][j]);
			}
			System.out.println();
		}
	}
	
	/**
	 * 输出Lasvt集合
	 */
	public void printLastvts(){
		System.out.printf("%5s","");
		for(int i=0;i< ends.size();i++){
			System.out.printf("%7s",  ends.get(i));
		}
		System.out.println();
		for(int i = 0;i< lastvts.length;i++){
			System.out.printf("%5s", starts.get(i));
			for(int j = 0;j<  lastvts[i].length;j++){
				System.out.printf("%7s", lastvts[i][j]);
			}
			System.out.println();
		}
	}
	
	/**
	 * 输出 优先关系表
	 */
	public void printYouxian(){
		System.out.printf("%6s","");
		for(char i: ends){
			System.out.printf("%6s", i);
		}
		System.out.println();
		for(int i = 0 ; i<  ends.size();i++){
			System.out.printf("%6s", ends.get(i));
			for(int j=0;j< ends.size();j++){
				if( youxian[i][j] == -1){
					System.out.printf("%6s","<");
				}else if( youxian[i][j] == 1){
					System.out.printf("%6s",">");
				}else if( youxian[i][j] == 0){
					System.out.printf("%6s","=");
				}else{
					System.out.printf("%6s","");
				}
			}
			System.out.println();
		}
	}
	
	
	public static void main(String[] args) {
		long startTime = System.currentTimeMillis();
		suanfu a = new suanfu();
		a.init();
		a.getStarts();
		a.getEnds();
		a.firstvts();
		a.lastvts();
		if( -1 == a.initYouxian() ){
			System.out.println("此文法不是算符优先文法");
			return;
		}
		/*
		a.printYouxian();
		
		for(fu i:a.fus){
			System.out.println(i.left+":"+i.ends);
		}
		*/
		a.anylize();
		long lastTime = System.currentTimeMillis();
		System.out.println("程序运行时间为："+(lastTime - startTime) +"ms");
	}
}


class fu {
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
