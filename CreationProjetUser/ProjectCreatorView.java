import javax.swing.*;
import java.util.*;
import java.awt.*;

public class ProjectCreatorView extends JPanel {
    private GridLayout gridL = new GridLayout(5, 1);

    private JPanel pathPanel = new JPanel();

    private JTextField[] textField = new JTextField[2];
    private JLabel newProjectTLabel = new JLabel("Chemin du projet");
    private JLabel newProjectNameJLabel = new JLabel("Nom du projet");
    private JButton findDirectoryButton = new JButton("...");

    public ProjectCreatorView() {

        this.setLayout(gridL);
        this.add(newProjectNameJLabel);
        textField[0] = new JTextField();
        textField[0].setText("DefaultProjet");
        this.add(textField[0]);
        this.add(newProjectTLabel);
        pathPanel.setLayout(new GridLayout(1, 3));
        pathPanel.add(textField[1] = new JTextField());
        findDirectoryButton.setPreferredSize(new Dimension(40, 40));
        pathPanel.add(findDirectoryButton);
        this.add(pathPanel);
    }

    public String getNameProject() {
        return this.textField[0].getText();
    }

    public String getPathProject() {
        return this.textField[1].getText();
    }

    public JButton getJButton() {
        return this.findDirectoryButton;
    }

    public JTextField[] gTextField() {
        return this.textField;
    }

}