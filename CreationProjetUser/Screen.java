import java.awt.*;
import java.io.IOException;
import java.util.*;
import javax.swing.*;

public class Screen extends JFrame {

    private String current;

    public Screen() {

        this.setLocation(500, 250);
        this.setMinimumSize(new Dimension(300, 250));
        this.setMaximumSize(new Dimension(400, 250));
        this.setResizable(false);
        this.setTitle("Launcher CAPS Engine");
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        try {
            current = new java.io.File(".").getCanonicalPath();
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        ProjectCreatorView pCV = new ProjectCreatorView();
        LFileChooser lFileC = new LFileChooser();
        pCV.getJButton().addActionListener(new ButtonListener(lFileC, pCV.gTextField()[1]));

        JButton validatioButton = new JButton("Valider");
        validatioButton.addActionListener(new ValidationButtonListener(this, pCV.gTextField()[0], pCV.gTextField()[1],
                lFileC, new CopyDirectory(), current));

        this.setLayout(new GridLayout(2, 1));
        this.add(pCV);
        this.add(validatioButton);
        this.setVisible(true);
    }

}
