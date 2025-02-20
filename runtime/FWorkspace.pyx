# FromiaGraphicalRuntime.pyx
# Import the GUI library and filesystem handling
from PyQt5.QtWidgets import QApplication, QMainWindow, QTreeView, QFileSystemModel, QVBoxLayout, QLabel, QDialog, QPushButton, QHBoxLayout
from PyQt5.QtGui import QIcon
from PyQt5.QtCore import QDir, Qt
import subprocess
import os
import sys

class FromiaWorkspace(QMainWindow):
    def __init__(self, root_dir):
        super().__init__()
        self.root_dir = root_dir

        # Set up the main window
        self.setWindowTitle("Fromia Runtime Workspace")
        self.setGeometry(100, 100, 800, 600)
        self.setWindowIcon(QIcon(os.path.join(root_dir, "Resources/icon.jpeg")))

        # Set up the layout and filesystem view
        self.initUI()

    def initUI(self):
        # File System View
        self.file_tree = QTreeView()
        self.model = QFileSystemModel()
        self.model.setRootPath(self.root_dir)
        self.file_tree.setModel(self.model)
        self.file_tree.setRootIndex(self.model.index(self.root_dir))
        self.file_tree.setColumnWidth(0, 250)
        self.file_tree.doubleClicked.connect(self.launchApp)

        # Status Bar
        self.status_bar = QLabel("Ready")
        self.statusBar().addWidget(self.status_bar)

        # Main Layout
        layout = QVBoxLayout()
        layout.addWidget(self.file_tree)

        central_widget = QMainWindow()
        central_widget.setLayout(layout)
        self.setCentralWidget(central_widget)

    def launchApp(self, index):
        file_path = self.model.filePath(index)
        if os.path.isdir(file_path):
            self.status_bar.setText(f"Selected Directory: {file_path}")
        elif os.path.isfile(file_path):
            # Try to execute the binary if it's part of a .crex structure
            crex_root = os.path.dirname(file_path)
            info_conf = os.path.join(crex_root, "Resources/Info.conf")

            if os.path.exists(info_conf):
                # Parse the Info.conf to find the executable
                with open(info_conf, "r") as f:
                    config = {}
                    for line in f:
                        if "=" in line:
                            key, value = line.strip().split("=", 1)
                            config[key] = value
                binary_path = os.path.join(crex_root, config.get("Executable", ""))
                if os.path.exists(binary_path):
                    # Execute the binary
                    self.status_bar.setText(f"Launching: {binary_path}")
                    try:
                        subprocess.Popen(binary_path, shell=True)
                    except Exception as e:
                        self.status_bar.setText(f"Error launching binary: {e}")
                else:
                    self.status_bar.setText("Executable not found in .crex structure.")
            else:
                self.status_bar.setText("Not a valid .crex structure.")

# Main Entry Point
def main():
    app = QApplication(sys.argv)
    root_dir = QDir.homePath()  # Default directory to browse .crex files
    runtime = FromiaWorkspace(root_dir)
    runtime.show()
    sys.exit(app.exec_())

# Run if executed directly
if __name__ == "__main__":
    main()
