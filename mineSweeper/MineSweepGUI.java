/*
 * need to:
 * complicate algorithm for placing mines
 * add in mine counter
 * add in victory sequence
 */
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Container;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

public class MineSweepGUI extends JFrame{
	
	private static final long serialVersionUID = 1L;
	
	public static void main(String[] args){
		new MineSweepGUI().setVisible(true);
	}
	
	public MineSweepLogic grid;
	
	private JButton newgame = new JButton("New Game");
	
	public int potentialmines=0;
	
	private JLabel potminecount = new JLabel ("     Mines" + potentialmines);
	
	private JButton[][] cells;
	
	public int initrow=0;
	
	public int initcol=0;
	
	public int minesnum=0;
	
	
			
	public MineSweepGUI(){
		do{
			String rowstring = JOptionPane.
			showInputDialog("Enter how many rows you want in this grid");
			try {
		        initrow = Integer.parseInt(rowstring);
		        }
			catch (NumberFormatException nfe) {
		          JOptionPane
		          .showMessageDialog(null, rowstring + " is not a valid integer");
			}
		}while(initrow<1);
		do{
			String colstring = JOptionPane.
			showInputDialog("Enter how many columns you want in this grid");
			try {
		        initcol = Integer.parseInt(colstring);
		        }
			catch (NumberFormatException nfe) {
		          JOptionPane
		          .showMessageDialog(null, colstring + " is not a valid integer");
			}
		}while(initcol<1);
		do{
			String minestring = JOptionPane.
			showInputDialog("Enter how many mines you want in this grid");
			try {
		        minesnum = Integer.parseInt(minestring);
		        }
			catch (NumberFormatException nfe) {
		          JOptionPane
		          .showMessageDialog(null, minestring + " is not a valid integer");
		          //try to get cancel to exit
			}
		}while(minesnum<1);
		grid = new MineSweepLogic(initrow, initcol, minesnum);
		potentialmines=minesnum;
		grid.ToString();
		setTitle("MineSweeper");
		setSize(800, 400);
		setLocation(250, 40);
		setResizable(false);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		
		JPanel panelwithcells = new JPanel();
	    panelwithcells.setLayout(new GridLayout(initrow, initcol));
		cells = new JButton[initrow][initcol];
		
	//	ButtonListener buttonListener = new ButtonListener();
		for(int i=0; i<initrow; i++){
			for(int j=0; j<initcol; j++){
				cells[i][j]= new JButton();
				cells[i][j].setBackground(Color.BLUE);
				cells[i][j].addMouseListener(new ButtonListener());
				cells[i][j].setBorder(BorderFactory.createMatteBorder(1, 1, 1, 1, Color.BLACK));
				cells[i][j].setText("  ");
				panelwithcells.add(cells[i][j]);
			}
		}
		
		Container cp = getContentPane();
	    cp.add(new JLabel("        "), BorderLayout.WEST);
	   // cp.add(new JLabel(), BorderLayout.EAST);
	    cp.add(panelwithcells, BorderLayout.CENTER);
	    
	    newgame.addActionListener(new ActionListener(){
	    	public void actionPerformed(ActionEvent ae){
	    		restart();
	    	}
	    });
	    JPanel topPanel = new JPanel();
	    topPanel.setLayout(new GridLayout(1, 3, 100, 7));
	    topPanel.add(newgame);
	    topPanel.add(potminecount);
//	    topPanel.add(potentialmines);
//	    cp.add
	    cp.add(topPanel, BorderLayout.NORTH);
	    }
	
		private class ButtonListener implements MouseListener {
			
//			public void actionPerformed(ActionEvent ae) {
//				JButton clickedbutton = (JButton) ae.getSource();
//				if(clickedbutton.getBackground().equals(Color.BLUE)){
//					clickedbutton.setBackground(Color.LIGHT_GRAY);
//					reveal();
//				}
//			}

			@Override
			public void mouseClicked(MouseEvent e) {
				JButton clickedbutton = (JButton) e.getSource();
				if(e.getButton()==1&&!(clickedbutton.getText().equals("F"))){
					if(clickedbutton.getBackground().equals(Color.BLUE)){
					clickedbutton.setBackground(Color.LIGHT_GRAY);
					reveal();
					}
				}
				if(e.getButton()==3){
					if(clickedbutton.getBackground().equals(Color.BLUE)){
						if(clickedbutton.getText().equals("  ")){
							clickedbutton.setText("F");
						}
						else if(clickedbutton.getText().equals("F")){
							clickedbutton.setText("?");
						}
						else
							clickedbutton.setText("  ");
					}
				}
			}

			@Override
			public void mouseEntered(MouseEvent e) {
				// TODO Auto-generated method stub
				
			}

			@Override
			public void mouseExited(MouseEvent e) {
				// TODO Auto-generated method stub
				
			}

			@Override
			public void mousePressed(MouseEvent e) {
				// TODO Auto-generated method stub
				
			}

			@Override
			public void mouseReleased(MouseEvent e) {
				// TODO Auto-generated method stub
				
			}
		}
		
		private void reveal(){
			for(int i=0; i<initrow; i++){
				for(int j=0; j<initcol; j++){
					if(cells[i][j].getBackground().equals(Color.LIGHT_GRAY)&&(cells[i][j].getText().equals("  ")||cells[i][j].getText().equals("?"))){
						if(grid.grid[i][j].equals("X"))
								cells[i][j].setText("X");
						else
							cells[i][j].setText(grid.MinesAround(i, j));
					}
					if(cells[i][j].getText().equals("X"))
						lose();
					else{
						if(cells[i][j].getText().equals(" "))
							revealaround(i, j);
					}
				}
			}
		}
		
		
		
		private void revealaround(int i, int j){
			for(int m=i-1; m<i+2; m++){
				for(int n=j-1; n<j+2; n++){
					if((m>=0)&&(n>=0)&&(m<grid.grid.length)&&(n<grid.grid[0].length)&&(m!=i||n!=j)){
						if(grid.MinesAround(m, n).equals(" ")&&(cells[m][n].getText().equals("  ")
								||cells[m][n].getText().equals("?"))){
							cells[m][n].setBackground(Color.LIGHT_GRAY);
							cells[m][n].setText(" ");
							revealaround(m, n);
						}
						if(grid.grid[m][n]!="X"&&!(cells[m][n].getText().equals("F"))){
							cells[m][n].setText(grid.MinesAround(m, n));
							cells[m][n].setBackground(Color.LIGHT_GRAY);
						}
					}
				}
			}
			
		}
		
		private void restart(){
			for(int i=0; i<initrow; i++){
				for(int j=0; j<initcol; j++){
					cells[i][j].setText("  ");
					cells[i][j].setBackground(Color.BLUE);
				}
			}
			MineSweepLogic temp = new MineSweepLogic(initrow, initcol, minesnum);
			grid=temp;
			grid.ToString();
		}
		
		private void lose(){
			for(int i=0; i<initrow; i++){
				for(int j=0; j<initcol; j++){
					if(grid.grid[i][j].equals("X"))
						cells[i][j].setText("X");
				}
			}
			JOptionPane.showMessageDialog(null, "You lost the game");
			restart();
		}
}
