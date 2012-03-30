
public class MineSweepLogic {
	
	String[][] grid;
	int rows, cols, mines;
	
	public MineSweepLogic(int i, int j, int request) throws IllegalArgumentException{
		if(i<0||j<0||request<0)
			throw new IllegalArgumentException("size not valid");
		grid = new String[i][j];
		rows=i;
		cols=j;
		mines=0;
		while(mines!=request){
		for(i=0; i<rows; i++){
			for(j=0; j<cols; j++){
				if(grid[i][j]!="X"&&mines!=request&&Math.random()<.20){
					grid[i][j]="X";
					mines++;
				}
			}
		}
		}
		for(i=0; i<rows; i++){
			for(j=0; j<cols; j++){
				if(grid[i][j]!="X"){
					grid[i][j]= MinesAround(i, j);
				}
			}
		}
	}

	public String MinesAround(int row, int col){
		
		int i, j;
		int count=0;
		for(i=row-1; i<row+2; i++){
			for(j=col-1; j<col+2; j++){
				if((i>=0)&&(j>=0)&&(i<grid.length)&&(j<grid[0].length)){
					if(grid[i][j]=="X"&&grid[i][j]!=grid[row][col])
						count++;
				}
			}
		}
		if(count==0)
			return " ";
		if(count==1)
			return "1";
		if(count==2)
			return "2";
		if(count==3)
			return "3";
		if(count==4)
			return "4";
		if(count==5)
			return "5";
		if(count==6)
			return "6";
		if(count==7)
			return "7";
		else
			return "8";
	}
	
	public String ToString(){
		String a= new String();
		for(int i=0; i<rows; i++){
			for(int j=0; j<cols; j++){
				a+=grid[i][j];
			}
			a+='\n';
		}
		System.out.println(a);
		return a;
	}
	
	public int minecount(){
		int check =0;
		for(int i=0; i<rows; i++){
			for(int j=0; j<cols; j++){
				if(grid[i][j]=="X")
					check++;
			}
		}
		return check;
	}
	
	public boolean minepresent(int i, int j){
		if(grid[i][j]=="X")
			return true;
		else
			return false;
	}
}