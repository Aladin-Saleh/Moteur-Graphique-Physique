import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;

import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JTextField;

public class ValidationButtonListener implements ActionListener {

    private JTextField jTextFieldName;
    private JTextField jTextFieldPath;
    private JFrame screen;
    private int condition;
    private CopyDirectory copyDirectory;
    private LFileChooser lFileChooser;
    private String cPath;

    public ValidationButtonListener(JFrame f, JTextField name, JTextField path, LFileChooser l,
            CopyDirectory pCopyDirectory, String currentPath) {
        this.screen = f;
        this.jTextFieldName = name;
        this.jTextFieldPath = path;
        this.condition = 0;
        this.lFileChooser = l;
        this.copyDirectory = pCopyDirectory;
        this.cPath = currentPath;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        // TODO Auto-generated method stub
        if (this.jTextFieldName.getText().equals("")) {
            System.err.println("Entrer un champ dans le nom du projet");
            JOptionPane.showMessageDialog(screen, "Entrer un champ dans le nom du projet");
            this.condition--;
        } else {
            System.out.println("Nom Valide !");
            this.condition++;
        }
        if (this.jTextFieldPath.getText().equals("")) {
            System.err.println("Entrer un champ dans le chemin");
            JOptionPane.showMessageDialog(screen, "Entrer un champ dans le chemin");
            this.condition--;
        } else {
            System.out.println("Chemin Valide !");
            this.condition++;
        }

        if (this.condition == 2) {
            File newRepertory = new File(this.jTextFieldName.getText());
            String copiedPath = this.cPath + "/ProjetVide";
            String destinedPath = this.jTextFieldPath.getText() + "/" + newRepertory.getName();
            String interfaceDllPath = this.cPath + "/../CapsEngine/CAPS/Header/InterfaceDll/";

            String destinedHeaderPath = this.jTextFieldPath.getText() + "/" + newRepertory.getName()
                    + "/CAPSDLL/Header/";
            String destinedSourcePath = this.jTextFieldPath.getText() + "/" + newRepertory.getName()
                    + "/CAPSDLL/Source/";

            String structHeaderPath = this.cPath + "/../CapsEngine/CAPS/Header/Struct/";
            String structSourcePath = this.cPath + "/../CapsEngine/CAPS/Source/Struct/";
            File src = new File(copiedPath);
            File dest = new File(destinedPath);
            File srcInterfaceDll = new File(interfaceDllPath);
            File destinationInterfaceDll = new File(destinedHeaderPath);
            File structHeader = new File(structHeaderPath);
            File structSource = new File(structSourcePath);
            File destinationSource = new File(destinedSourcePath);

            try {

                copyDirectory.copyD(src, dest);
                copyDirectory.copyD(srcInterfaceDll, destinationInterfaceDll);
                copyDirectory.copyD(structHeader, destinationInterfaceDll);
                copyDirectory.copyD(structSource, destinationSource);

            } catch (IOException exc) {
                exc.printStackTrace();
            }

        }

    }

}
