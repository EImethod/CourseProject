import java.io.*;
import javax.swing.*;
import java.awt.*;
import java.util.*;
import javax.swing.event.*;
import java.awt.event.*;

public class JavaNotepad extends JFrame {
	JTextArea jTextArea;
	File selF;
	JLabel jLabel;
	JMenuBar jMenuBar;
	JMenu JMenuFile, JMenuEdit, JMenuAbout;
	JMenuItem JMIOpen, JMISave, JMISaveAs, JMIClose, JMICopy, JMICut, JMIPaste,
			JMIAbout;
	JPopupMenu JPM;

	public JavaNotepad() { // JFrame Ĭ�ϵ���BorderLayout
		super("�½��ı��ĵ�");
		this.setSize(500, 500);
		initUI();
		initListener();
	}

	private void initUI() {
		//ȡ��ϵͳ֧�ֵ�����
		GraphicsEnvironment e = GraphicsEnvironment
				.getLocalGraphicsEnvironment();
		Font[] f = e.getAllFonts();
		//for (Font s : f) {
		//	System.out.println(s.getFontName());
		//}
		JMenuFile = new JMenu("�ļ�");
		JMenuEdit = new JMenu("�༭");
		JMenuAbout = new JMenu("����");
		JMIOpen = new JMenuItem("��"); // �������ÿ�ݼ�
		JMIOpen.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_O,
				InputEvent.CTRL_MASK));
		JMISave = new JMenuItem("����");
		JMISave.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_S,
				InputEvent.CTRL_MASK));
		JMISaveAs = new JMenuItem("���Ϊ");
		JMIClose = new JMenuItem("�ر�");
		JMIClose.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_Q,
				InputEvent.CTRL_MASK));
		JMICut = new JMenuItem("����");
		JMICut.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_X,
				InputEvent.CTRL_MASK));
		JMICopy = new JMenuItem("����");
		JMICopy.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_C,
				InputEvent.CTRL_MASK));
		JMIPaste = new JMenuItem("ճ��");
		JMIPaste.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_V,
				InputEvent.CTRL_MASK));
		JMIAbout = new JMenuItem("����daodao���±�");

		JMenuFile.add(JMIOpen);

		JMenuFile.add(JMISave);
		JMenuFile.add(JMISaveAs);
		JMenuFile.add(JMIClose);
		JMenuEdit.add(JMICut);
		JMenuEdit.add(JMICopy);
		JMenuEdit.add(JMIPaste);
		JMenuAbout.add(JMIAbout);
		jMenuBar = new JMenuBar();
		jMenuBar.add(JMenuFile);
		jMenuBar.add(JMenuEdit);
		jMenuBar.add(JMenuAbout);
		
		JPM = JMenuEdit.getPopupMenu(); // ȡ����˵������ĵ���ʽ�˵�
		this.add(jMenuBar, BorderLayout.NORTH); // ��ӵ�ʱ����Ҫͬʱ�ƶ����ֹ������еķ�λ
		jTextArea = new JTextArea(); //
		jTextArea.setFont(new Font("΢���ź�", Font.BOLD | Font.PLAIN, 24));
		jTextArea.setForeground(Color.RED);
		jTextArea.setLineWrap(true); // �Զ�����
		JScrollPane jsp = new JScrollPane(jTextArea); // ����������������
		this.add(jsp, BorderLayout.CENTER);

		jLabel = new JLabel("δ�޸�");
		this.add(jLabel, BorderLayout.SOUTH);

		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setVisible(true);
	}

	private void initListener() { // ע�������
		JMIOpen.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				openFile();
			}
		});
		JMISave.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				Save();
			}
		});
		JMISaveAs.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				SaveAs();
			}
		});
		JMIClose.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if (jLabel.getText().compareTo("���޸�") == 0) {
					int result = JOptionPane.showConfirmDialog(null,
							"�ļ����޸�,Ҫ������?");
					if (result == JOptionPane.OK_OPTION) {
						SaveAs();
					} else if (result == JOptionPane.OK_CANCEL_OPTION) {
						return;
					}
				}
				System.exit(0);
			}
		});
		JMICut.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				jTextArea.cut();
			}
		});
		JMICopy.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				jTextArea.copy();
			}
		});
		JMIPaste.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				jTextArea.paste();
			}
		});
		/*JMenuEdit.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				System.out.println("xixi");
				JPM.show(null, JMenuEdit.getX(), JMenuEdit.getY()); 
			}
		});*/
		// ��ʾһЩȷ����Ϣ�ȵĶԻ�������� JOptionPane,�ܺ���
		JMIAbout.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				JOptionPane
						.showMessageDialog(null,
								"^_^߶߶������Ʒ\n��������: 2010.12.17\n����zjut_DD\nAll Right Reserved");
			}
		});
		// ��������click,�Ҽ���press,release******o(�s���t)o**
		jTextArea.addMouseListener(new MouseAdapter() {
			public void mousePressed(MouseEvent e) { // ����һ����д������*****
				if (e.isPopupTrigger()) {
					JPM.show(jTextArea, e.getX(), e.getY()); // ������һ��Ҫ����ΪjTextArea�ź���
				}
			}

			public void mouseReleased(MouseEvent e) {
				if (e.isPopupTrigger()) {
					JPM.show(jTextArea, e.getX(), e.getY());
				}
			}
		});
		jTextArea.addKeyListener(new KeyAdapter() {
			public void keyPressed(KeyEvent e) {
				if (e.isControlDown() && e.getKeyChar() == KeyEvent.VK_S) { // �ж��ǲ���ctrl+s����ϼ�
					Save();
					jLabel.setText("δ�޸�");
				} else {
					jLabel.setText("���޸�");
				}
			}
		});
	}

	private void SaveAs() { // �ļ����Ϊ
		JFileChooser jFileChooser = new JFileChooser();
		jFileChooser.showSaveDialog(null);
		selF=jFileChooser.getSelectedFile();
		this.setTitle(selF.getName());
		try {
			FileWriter fWriter = new FileWriter(jFileChooser.getSelectedFile());
			jTextArea.write(fWriter);
		} catch (Exception e) {

		}
	}

	private void Save() { // �����ļ�
		if (selF == null) {
			SaveAs();
			jLabel.setText("δ�޸�");
		}
		try {
			FileWriter fWriter = new FileWriter(selF);
			jTextArea.write(fWriter);
			jLabel.setText("δ�޸�");
		} catch (Exception e) {

		}
	}

	private void openFile() { // ��һ���ı��ļ�
		JFileChooser jFileChooser = new JFileChooser();
		jFileChooser.showOpenDialog(null);
		selF = jFileChooser.getSelectedFile();
		this.setTitle(selF.getName());
		try {
			jTextArea.setText("");
			Scanner reader = new Scanner(selF);
			String line;
			while (reader.hasNext()) {
				line = reader.nextLine();
				jTextArea.append(line);
				jTextArea.append("\n");
			}
			jLabel.setText("δ�޸�");
		} catch (Exception e) {

		}
	}

	public static void main(String[] args) {
		JavaNotepad javatext = new JavaNotepad();
	}
}
