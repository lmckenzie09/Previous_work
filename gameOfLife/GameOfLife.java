public class GameOfLife {
	char[][] cellfield;
	int rows = 0, cols = 0, cycle = 0;

	public GameOfLife(int i, int j) {
		if (i <= 0 || j <= 0)
			return;
		else {
			cellfield = new char[i][j];
			rows = cellfield.length;
			cols = cellfield[0].length;
			for (i = 0, j = 0; i < rows; j++) {
				cellfield[i][j] = '*';
				if (j == cols - 1) {
					j = -1;
					i++;
				}
			}
		}
	}

	public int numberOfRows() {
		return rows;
	}

	public int numberOfColumns() {
		return cols;
	}

	public boolean cellAt(int r, int c) {
		if (r < 0 || c < 0)
			return false;
		if (r >= rows || c >= cols)
			return false;
		if (cellfield[r][c] == 'O')
			return true;
		else
			return false;
	}

	public void growCellAt(int i, int j) {
		if(cellfield[i][j]== 'O')
			return;
		if (i < 0 || j < 0)
			return;
		if (i >= rows || j >= cols)
			return;
		cellfield[i][j] = 'O';
	}
	
	public void killCellAt(int i, int j) {
		if (cellfield[i][j]== '*')
			return;
		if (i < 0 || j < 0)
			return;
		if (i >= rows || j >= cols)
			return;
		cellfield[i][j] = '*';
	}

	public String ToString() {
		String cellgui = new String();
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				cellgui += cellfield[i][j];
			}
			cellgui += '\n';
		}
		cycle++;
		cellgui += '\n' + "Generation " + cycle + '\n';
		return cellgui;
	}

	public int neighborCount(int i, int j) {
		if (i < 0 || j < 0)
			return 0;
		if (i >= rows || j >= cols)
			return 0;
		int subi = 0, subj = 0, posi = 0, posj = 0, count = 0;
		if (i - 1 < 0)
			subi = i + (rows - 1);
		else
			subi = i - 1;
		if (j - 1 < 0)
			subj = j + (cols - 1);
		else
			subj = j - 1;
		if (i + 1 == rows)
			posi = 0;
		else
			posi = i + 1;
		if (j + 1 == cols)
			posj = 0;
		else
			posj = j + 1;
		if (rows > 1) {
			if (cellfield[posi][j] != '*')
				count++;
		}
		if (cols > 1) {
			if (cellfield[i][posj] != '*')
				count++;
		}
		if (rows > 1 && cols > 1) {
			if (cellfield[posi][posj] != '*')
				count++;
		}
		if (rows > 2) {
			if (cellfield[subi][j] != '*')
				count++;
			if (cols > 1) {
				if (cellfield[subi][posj] != '*')
					count++;
			}
		}
		if (cols > 2) {
			if (cellfield[i][subj] != '*')
				count++;
			if (rows > 1) {
				if (cellfield[posi][subj] != '*')
					count++;
			}
		}
		if (rows > 2 && cols > 2) {
			if (cellfield[subi][subj] != '*')
				count++;
		}
		return count;
	}

	public void update() {
		if (cycle == 0)
			System.out.println(ToString());
		char[][] temp = new char[rows][cols];
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				if (cellfield[i][j] == '*') {
					if (this.neighborCount(i, j) == 3)
						temp[i][j] = 'O';
					else
						temp[i][j] = '*';
				} else {
					if (this.neighborCount(i, j) > 1
							&& this.neighborCount(i, j) < 4)
						temp[i][j] = 'O';
					else
						temp[i][j] = '*';
				}
			}
		}
		cellfield = temp;
		System.out.println(ToString());
	}
}
