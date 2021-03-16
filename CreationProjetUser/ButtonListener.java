import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JTextField;

public class ButtonListener implements ActionListener {

    private LFileChooser lFileChooser;
    private JTextField jTF;

    public ButtonListener(LFileChooser l, JTextField j) {
        this.lFileChooser = l;
        this.jTF = j;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        // TODO Auto-generated method stub
        this.jTF.setText(this.lFileChooser.dialog());
        System.out.println(this.jTF.getText());
    }

}