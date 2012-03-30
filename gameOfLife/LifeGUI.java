/**
 *
 * This GameOfLifeGUI class allows
 *    You to set up an initial society and step through it or run it by clicking Start.
 *    You can also select from a few initial societies.
 *
 *    You can also change the amount of time between updates in milliseconds.
 *
 * @author Rick Mercer
 * @version Spring 2008
 * @updated Spring 2011 by Lloyd McKenzie
 * updates: 
 * -added a max counter and a cell counter
 * -rearranged button position
 * -fixed cell clicks
 * -fixed clear usage
 * -fixed step usage
 * -allowed for deletion of individual cells while paused
 * -increased size of gameboard, and allowed resizing of window
 * -took away border
 * -added Quadruple, Wavy, Stairway, F-Pentamino, TriForce, Naturals, and Blinkers preloads
 */

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Container;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.Timer;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

public class LifeGUI extends JFrame {

  private static final long serialVersionUID = 1L;

  public static void main(String[] args) {
    new LifeGUI().setVisible(true);
  }

  private GameOfLife society;

  private JButton stepButton = new JButton("Step");

  private JButton animationButton = new JButton("Start");

  private JButton clearButton = new JButton("Clear");

  private JComboBox selections;

  private JLabel updateCounterLabel = new JLabel("Updates: ");
  
  private int cellcount = 0;
  
  private int maxnum = 0;
  
  private int rank = 0;
  
  private int rank2 = 0;
  
  private JLabel maxcellnum = new JLabel("       Max: " + maxnum);
  
  private JLabel updateCellCount = new JLabel("Cells: " + cellcount);

  private Timer timer;

  private int delay = 500; // Milliseconds

  private int updateCounter = 0;
  
  

  private String[] list = { "Pre Made", "Gliders", "Queen", "Mystery", "Quadruple", 
		  "Wavy", "Stairway", "F-Pentomino", "TriForce", "Naturals", "Blinkers" };

  private JSlider sliderBar;

  public static int ROWS = 81;

  public static int COLS = 111;

  private boolean frozen = true;

  private JButton[][] cells;

  public LifeGUI() {
    setTitle("John Conway's Game of Life");
    setSize(880, 630);
    setLocation(200, 80);
    setResizable(true);
    setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

    society = new GameOfLife(ROWS, COLS);
    JPanel panelWithCells = new JPanel();
    panelWithCells.setLayout(new GridLayout(ROWS, COLS));
    cells = new JButton[ROWS][COLS];

    clearButton.addActionListener(new ClearButtonListener());

    //ButtonListener buttonListener = new ButtonListener();
    for (int r = 0; r < ROWS; r++)
      for (int c = 0; c < COLS; c++) {
        cells[r][c] = new JButton();
        cells[r][c].setBackground(Color.LIGHT_GRAY);
        cells[r][c].addActionListener(new ButtonListener());
        //took bordersize down to 0 to get rid of border to get more screen real estate
       cells[r][c].setBorder(BorderFactory.createMatteBorder(0, 0, 0, 0,
           Color.LIGHT_GRAY));
       //added in settext to initialize all cells to eliminate need to click twice
        cells[r][c].setText(" ");
        panelWithCells.add(cells[r][c]);
      }

    Container cp = getContentPane();
    cp.add(new JLabel("         "), BorderLayout.WEST);
    cp.add(new JLabel(), BorderLayout.EAST);
    cp.add(panelWithCells, BorderLayout.CENTER);
    animationButton.addActionListener(new AnimationButtonListener());
    stepButton.addActionListener(new StepButtonListener());

    selections = new JComboBox(list);
    selections.addActionListener(new SelectionListener());
    JPanel topPanel = new JPanel();
    /**took vgap down by half for RE, and added maxcellnum, and updatecellcount labels 
     * to track max # of cells and how many cells at any given time. also rearranged 
     * previous buttons
     */
    topPanel.setLayout(new GridLayout(1, 7, 50, 5));
    topPanel.add(maxcellnum);
    topPanel.add(clearButton);
    topPanel.add(selections);
    topPanel.add(animationButton);
    topPanel.add(stepButton);
    topPanel.add(updateCounterLabel);
    topPanel.add(updateCellCount);
    cp.add(topPanel, BorderLayout.NORTH);
    sliderBar = new JSlider();
    sliderBar = new JSlider(JSlider.HORIZONTAL, 0, 2000, delay);
    sliderBar.addChangeListener(new SliderListener());

    // Turn on labels at major tick marks.
    sliderBar.setMajorTickSpacing(100);
    //changed minor tick spacing from 1 to 10
    sliderBar.setMinorTickSpacing(10);
    sliderBar.setPaintTicks(true);
    sliderBar.setPaintLabels(true);
    JPanel p = new JPanel();
    p.setLayout(new BorderLayout());
    p.add(sliderBar, BorderLayout.CENTER);
    p.add(new JLabel(" Delay in milliseconds ", JLabel.CENTER),
        BorderLayout.SOUTH);
    cp.add(p, BorderLayout.SOUTH);

    setUpTimer();
  }

  public void setUpTimer() {
    timer = new Timer(delay, new SocietyUpdater());
    timer.setInitialDelay(0);
    timer.setCoalesce(true);
  }

  // From the Java Tutorial
  // Can be invoked by any thread (since timer is thread-safe).
  public void startAnimation() {
    if (!frozen && !timer.isRunning()) {
      timer.start();
    }
  }

  // From the Java Tutorial
  // Can be invoked by any thread (since timer is thread-safe).
  public void stopAnimation() {
    // Stop the animating thread.
    if (timer.isRunning())
      timer.stop();
  }

  private class SocietyUpdater implements ActionListener {
    public void actionPerformed(ActionEvent ae) {
      updateCounterLabel.setText("Updates: " + ++updateCounter);
      readTheButtons();
      society.update();
      updateButtons();
    }
  }

  // Adapted from the Java Tutorial
  private class AnimationButtonListener implements ActionListener {
    public void actionPerformed(ActionEvent ae) {
      if (frozen) {
        frozen = false;
        animationButton.setText("Stop ");
        startAnimation();
      } else {
        frozen = true;
        animationButton.setText("Start");
        stopAnimation();
      }
    }
  }

  private class SliderListener implements ChangeListener {
    public void stateChanged(ChangeEvent arg0) {
      timer.setDelay(sliderBar.getValue());
    }
  }
//plugged in updatecellcount to change when cells are clicked individually
  private class ButtonListener implements ActionListener {
    public void actionPerformed(ActionEvent ae) {
    	if(frozen){
      JButton clickedButton = (JButton) ae.getSource();
      if (clickedButton.getText().equals(" ")) {
        clickedButton.setText("^");
        updateCellCount.setText("Cells: " + ++cellcount);
      } else {
        clickedButton.setText(" ");
        updateCellCount.setText("Cells: " + --cellcount);
      }
    	}
    }
  }
//added in updatecounter so update will also work with stepbutton
//and changed frozen statement so that the start button changes properly
  private class StepButtonListener implements ActionListener {
    public void actionPerformed(ActionEvent e) {
      	if(frozen==false){
            frozen = true;
            animationButton.setText("Start");
            stopAnimation();
    	}
      readTheButtons();
      society.update();
      updateButtons();
      updateCounterLabel.setText("Updates: " + ++updateCounter);
    }
  }
//added in ability to kill any given cell 
  private void readTheButtons() {
    for (int r = 0; r < society.numberOfRows(); r++)
      for (int c = 0; c < society.numberOfColumns(); c++){
        if (cells[r][c].getText().equals("^"))
        	society.growCellAt(r, c);
        else if(society.cellAt(r, c)==true)
        	society.killCellAt(r, c);
      }
  }
  //necessary new method to properly load preloaded seeds since updatebuttons was changed
  private void updatepreload() {
	  for (int r = 0; r < society.numberOfRows(); r++)
	      for (int c = 0; c < society.numberOfColumns(); c++)
	        if (society.cellAt(r, c)) {
	          cells[r][c].setText("^");
  }
  }
//now also keeps track of number of cells and max number of cells reached
  public void updateButtons() {
	  cellcount=0;
    for (int r = 0; r < society.numberOfRows(); r++)
      for (int c = 0; c < society.numberOfColumns(); c++)
        if (society.cellAt(r, c)) {
          cells[r][c].setText("^");
          cellcount++; 
        } else {
          cells[r][c].setText(" ");
        }
    updateCellCount.setText("Cells: " + cellcount);
    if(cellcount>maxnum){
    	maxnum=cellcount;
    	maxcellnum.setText("       Max: " + maxnum);
    }
  }

  private class ClearButtonListener implements ActionListener {
    public void actionPerformed(ActionEvent ae) {
      clearButtons();
    }
  }
//will now also signal the start/stop button to switch when pressed while sim is running
  private void clearButtons() {
    society = new GameOfLife(ROWS, COLS);
	if(frozen==false){
        frozen = true;
        animationButton.setText("Start");
	}
    this.stopAnimation();
    updateCounter = 0;
    cellcount = 0;
    maxnum = 0;
    rank=0;
    rank2=0;
    updateCounterLabel.setText("Updates: " + updateCounter);
    updateCellCount.setText("Cells: " + cellcount);
    maxcellnum.setText("       Max: " + cellcount);

    for (int r = 0; r < society.numberOfRows(); r++)
      for (int c = 0; c < society.numberOfColumns(); c++) {
        cells[r][c].setText(" ");
      }
  }
//when choosing selection mid sim, prog pauses as expected, can now call up multiple
  //preloads at once
  private class SelectionListener implements ActionListener {
    public void actionPerformed(ActionEvent ae) {
    	if(frozen==false){
            frozen = true;
            animationButton.setText("Start");
    	}
      stopAnimation();
      JComboBox theList = (JComboBox) ae.getSource();
      int index = theList.getSelectedIndex();
      String choice = list[index];
      if (choice.equals("Queen"))
        queen();
      else if (choice.equals("Gliders"))
        gliders();
      else if (choice.equals("Mystery"))
        mystery();
      else if (choice.equals("Quadruple"))
    	  quadruple();
      else if (choice.equals("Wavy"))
    	  wavy();
      else if (choice.equals("Stairway"))
    	  stairway();
      else if (choice.equals("F-Pentomino"))
    	  fpento();
      else if (choice.equals("TriForce"))
    	  triforce();
      else if (choice.equals("Naturals"))
    	  naturals();
      else if (choice.equals("Blinkers"))
    	  blinkers();
      updatepreload();
      readTheButtons();		
      updateButtons();
    }
  }

  private void queen() {
    // queen
    society = new GameOfLife(ROWS, COLS);
    society.growCellAt(10, 21);
    society.growCellAt(11, 21);
    society.growCellAt(12, 22);
    society.growCellAt(13, 23);
    society.growCellAt(13, 24);
    society.growCellAt(13, 25);
    society.growCellAt(12, 26);
    society.growCellAt(11, 27);
    society.growCellAt(10, 27);
  }

  private void gliders() {
    // gliders
    society = new GameOfLife(ROWS, COLS);
    for (int i = 0; i < 40; i += 8) {
      society.growCellAt(5, 10 + i);
      society.growCellAt(6, 11 + i);
      society.growCellAt(6, 12 + i);
      society.growCellAt(7, 11 + i);
      society.growCellAt(7, 10 + i);
    }
  }

  private void mystery() {
    society = new GameOfLife(ROWS, COLS);
    society.growCellAt(5, 5);
    society.growCellAt(6, 4);
    society.growCellAt(6, 6);
    society.growCellAt(7, 4);
    society.growCellAt(7, 6);
    society.growCellAt(8, 5);
    society.growCellAt(5, 15);
    society.growCellAt(6, 14);
    society.growCellAt(6, 16);
    society.growCellAt(7, 15);
    society.growCellAt(7, 16);
    society.growCellAt(5, 25);
    society.growCellAt(5, 26);
    society.growCellAt(6, 25);
    society.growCellAt(6, 27);
    society.growCellAt(7, 26);
    society.growCellAt(7, 27);
    society.growCellAt(5, 35);
    society.growCellAt(5, 36);
    society.growCellAt(6, 34);
    society.growCellAt(6, 37);
    society.growCellAt(7, 37);
    society.growCellAt(7, 35);
    society.growCellAt(8, 36);
  }
  
  private void quadruple(){
	  society = new GameOfLife(ROWS, COLS);
	  society.growCellAt(14, 35);
	  society.growCellAt(16, 35);
	  society.growCellAt(15, 34);
	  society.growCellAt(15, 36);
	  society.growCellAt(16, 34);
	  society.growCellAt(16, 36);
	  society.growCellAt(17, 35);
	  
	  society.growCellAt(19, 31);
	  society.growCellAt(19, 30);
	  society.growCellAt(20, 29);
	  society.growCellAt(20, 31);
	  society.growCellAt(20, 32);
	  society.growCellAt(21, 30);
	  society.growCellAt(21, 31);
	  
	  society.growCellAt(23, 35);
	  society.growCellAt(24, 35);
	  society.growCellAt(24, 34);
	  society.growCellAt(24, 36);
	  society.growCellAt(25, 34);
	  society.growCellAt(25, 36);
	  society.growCellAt(26, 35);
	  
	  society.growCellAt(19, 40);
	  society.growCellAt(19, 39);
	  society.growCellAt(20, 38);
	  society.growCellAt(20, 39);
	  society.growCellAt(20, 41);
	  society.growCellAt(21, 39);
	  society.growCellAt(21, 40);
  }
  private void wavy(){
	  society = new GameOfLife(ROWS, COLS);
	  society.growCellAt(40, 46);
	  society.growCellAt(39, 47);
	  society.growCellAt(40, 48);
	  society.growCellAt(39, 49);
	  society.growCellAt(40, 50);
	  society.growCellAt(39, 51);
	  society.growCellAt(40, 52);
	  society.growCellAt(39, 53);
	  society.growCellAt(40, 54);
	  society.growCellAt(39, 55);
	  society.growCellAt(40, 56);
	  society.growCellAt(39, 57);
	  society.growCellAt(40, 58);
	  society.growCellAt(39, 59);
	  society.growCellAt(40, 60);
	  society.growCellAt(39, 61);
	  society.growCellAt(40, 62);
	  society.growCellAt(39, 63);
	  society.growCellAt(40, 64);
  }
  
  private void stairway(){
	  society = new GameOfLife(ROWS, COLS);
	  society.growCellAt(29, 69);
	  society.growCellAt(29, 70);
	  society.growCellAt(30, 70);
	  society.growCellAt(30, 71);
	  society.growCellAt(31, 71);
	  society.growCellAt(31, 72);
	  society.growCellAt(32, 72);
	  society.growCellAt(32, 73);
  }
  
  private void fpento(){
	  society = new GameOfLife(ROWS, COLS);
	  society.growCellAt(28, 80);
	  society.growCellAt(28, 81);
	  society.growCellAt(29, 80);
	  society.growCellAt(29, 79);
	  society.growCellAt(30, 80);
  }
  
  private void triforce(){
	  society = new GameOfLife(ROWS, COLS);
	  society.growCellAt(14, 55);
	  society.growCellAt(16, 54);
	  society.growCellAt(16, 56);
	  society.growCellAt(18, 57);
	  society.growCellAt(18, 55);
	  society.growCellAt(18, 53);
	  society.growCellAt(20, 52);
	  society.growCellAt(20, 54);
	  society.growCellAt(20, 56);
	  society.growCellAt(20, 58);
	  
	  society.growCellAt(22, 51);
	  society.growCellAt(24, 50);
	  society.growCellAt(24, 52);
	  society.growCellAt(26, 53);
	  society.growCellAt(26, 51);
	  society.growCellAt(26, 49);
	  society.growCellAt(28, 48);
	  society.growCellAt(28, 50);
	  society.growCellAt(28, 52);
	  society.growCellAt(28, 54);
	  
	  society.growCellAt(22, 59);
	  society.growCellAt(24, 58);
	  society.growCellAt(24, 60);
	  society.growCellAt(26, 61);
	  society.growCellAt(26, 59);
	  society.growCellAt(26, 57);
	  society.growCellAt(28, 56);
	  society.growCellAt(28, 58);
	  society.growCellAt(28, 60);
	  society.growCellAt(28, 62);
  }
  //choose this repeatedly from the list to create a new structure, shifted 3 cells
  //to the right
  private void naturals(){
	  society = new GameOfLife(ROWS, COLS);
	  society.growCellAt(40, 30+(rank*3));
	  society.growCellAt(41, 30+(rank*3));
	  society.growCellAt(41, 31+(rank*3));
	  society.growCellAt(42, 31+(rank*3));
	  rank++;
  }
  //choose this repeatedly from the list to create a new structure, just shifted over
  private void blinkers(){
	  society = new GameOfLife(ROWS, COLS);
	  society.growCellAt(25, 14+(rank2*18));
	  society.growCellAt(26, 14+(rank2*18));
	  society.growCellAt(26, 15+(rank2*18));
	  society.growCellAt(27, 15+(rank2*18));
	  society.growCellAt(25, 17+(rank2*18));
	  society.growCellAt(27, 18+(rank2*18));
	  society.growCellAt(25, 20+(rank2*18));
	  society.growCellAt(26, 20+(rank2*18));
	  society.growCellAt(26, 21+(rank2*18));
	  society.growCellAt(27, 21+(rank2*18));
	  rank2++;
  }
  
}
