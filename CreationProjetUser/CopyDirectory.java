import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardCopyOption;

public class CopyDirectory {

    // private int SIZE_BUFFER = 65536 * 1600;

    public void copyD(File source, File destination) throws IOException {

        if (source.isDirectory()) {
            // si le répertoire n'existe pas, créez-le
            if (!destination.exists()) {
                destination.mkdir();
                System.out.println("Dossier " + source + "  > " + destination);
            }

            // lister le contenu du répertoire
            String files[] = source.list();
            for (String f : files) {
                // construire la structure des fichiers source et destination
                File sourceF = new File(source, f);
                File destinationF = new File(destination, f);
                // copie récursive
                copyD(sourceF, destinationF);
            }
        } else {

            // la solution de mon coeur <3
            /*
             * InputStream in = new FileInputStream(source); OutputStream out = new
             * FileOutputStream(destination);
             * 
             * byte[] buffer = new byte[SIZE_BUFFER]; int length; // copier le contenu du
             * fichier while ((length = in.read(buffer)) > 0) { out.write(buffer, 0,
             * length); }
             * 
             * in.close(); out.close();
             */
            Files.copy(source.toPath(), destination.toPath(), StandardCopyOption.REPLACE_EXISTING);
            System.out.println("Fichier " + source + " > " + destination);
        }
    }

}
