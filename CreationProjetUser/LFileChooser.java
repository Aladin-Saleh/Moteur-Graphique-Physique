import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.nio.file.DirectoryStream;
import java.nio.file.Files;
import java.io.FileWriter;
import java.io.IOException;

import javax.swing.JFileChooser;

public class LFileChooser {

    JFileChooser chooser;
    String choosertitle;

    public String dialog() {

        int result;

        chooser = new JFileChooser();
        chooser.setCurrentDirectory(new java.io.File("."));
        chooser.setDialogTitle(choosertitle);
        chooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);

        chooser.setAcceptAllFileFilterUsed(false);
        //
        if (chooser.showOpenDialog(null) == JFileChooser.APPROVE_OPTION) {

            System.out.println("getCurrentDirectory(): " + chooser.getCurrentDirectory());
            System.out.println("getSelectedFile() : " + chooser.getSelectedFile());

            return chooser.getSelectedFile().toString();

        } else {

            System.out.println("No Directory selected");
            return null;
        }
    }

    public String getCurrentDirectory() {
        return chooser.getCurrentDirectory().toString();
    }

}