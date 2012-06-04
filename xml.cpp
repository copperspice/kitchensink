#include "xml.h"
#include "util.h"

#include <QDomDocument>
#include <QMessageBox>
#include <QFileDialog>
#include <QStandardItemModel>

Xml::Xml(Mdi *parent)
   : QWidget(), ui(new Ui::Xml)
{     
   ui->setupUi(this);
   setWindowTitle("XML");

   QStandardItemModel *model = new QStandardItemModel;
   ui->treeView->setModel(model);

   // signals
   connect(ui->openPB,  SIGNAL(clicked()), this, SLOT(actionOpenXml()));
   connect(ui->closePB, SIGNAL(clicked()), this, SLOT(actionClose()));
}

Xml::~Xml()
{
   delete ui;
}

void Xml::actionOpenXml()
{
   QString fileName = QFileDialog::getOpenFileName(this, tr("Open XML File"),
            QDir::currentPath(), tr("XML Files (*.xml)"));

   if (fileName.isEmpty()) {
      return;
   }

   QFile file(fileName);
   if (!file.open(QFile::ReadOnly | QFile::Text)) {

      const QString msg = "Unable to open file " + fileName + " : " + file.errorString();
      QMessageBox::warning( 0, "XML", msg );

      return;
   }

   //
   QDomDocument doc("menu");

   // error message will be placed in *errorMsg
   QString errorMsg;
   int errorLine;
   int errorColumn;

   if (! doc.setContent(&file, false, &errorMsg, &errorLine, &errorColumn)) {
     file.close();

     const QString msg = "Set Content failed.   \n\nError:" + errorMsg + "\n" +
         "Line: " + QString::number(errorLine) + "  Column: " + QString::number(errorColumn);

     QMessageBox::warning( this, "XML", msg );
     return;
   }

   file.close();

   // parse xml, test root element
   QDomElement root = doc.documentElement();

   if (root.tagName() != "menu")  {
      const QString msg = "XML root element must be 'menu'";
      QMessageBox::warning( this, "XML", msg );
      return;
   }

   // QStandardItemModel::insertRow ( int row, QStandardItem * item )

   ksMsg("add item now "+ root.tagName() );




}

void Xml::actionClose() {
   this->parentWidget()->close();
}



/*

void R_Xml::exportXml()
{

   QString fileName = QFileDialog::getSaveFileName( 0, "Export Recipe", QDir::currentPath() + "\\" + m_rData.rName, "XML Files (*.xml)" );
   if (fileName.isEmpty()) {
      return;
   }

   QFile file(fileName);
   if (!file.open(QFile::WriteOnly | QFile::Text)) {
      const QString msg = "Unable to save file " + fileName + " : " + file.errorString();
      QMessageBox::warning( 0, "Export Recipe", msg );
      return;
   }

   // just the file name, nothing more
   QFileInfo fileInfo(fileName);
   QString baseName = fileInfo.baseName();

   QDomDocument doc;

   // encoding
   QDomProcessingInstruction xml =  doc.createProcessingInstruction("xml", " version=\"1.0\" encoding=\"UTF-8\"");
   doc.appendChild(xml);

   // dtd
   QDomImplementation implement;
   QDomDocumentType dtdType = implement.createDocumentType("recipe", 0, "recipe.dtd");
   doc.appendChild(dtdType);

   // root
   QDomElement root = doc.createElement("recipe");
   doc.appendChild(root);

   // 1
   QDomElement tag = doc.createElement("rName");
   root.appendChild(tag);

   tag.appendChild(doc.createTextNode(m_rData.rName));

   // 2
   tag = doc.createElement("submitBy");
   root.appendChild(tag);

   tag.appendChild(doc.createTextNode(m_rData.rSubmitBy));

   // 3
   tag = doc.createElement("categories");
   root.appendChild(tag);

   tag.appendChild(doc.createTextNode(m_rData.rRecipeKind));


   // ingredients
   QList<ingredientList>::const_iterator nK;

   ingredientList item;
   QString units;

   QDomElement tagIngredients = doc.createElement("ingredients");
   root.appendChild(tagIngredients);

   QDomElement tagItem;

   for (nK = m_itemList.begin(); nK != m_itemList.end(); ++nK )
   {
      item = *nK;

      units = item.unitName;
      if ( units == "(blank)") {
         units = "";
      }

      // item
      tagItem = doc.createElement("item");
      tagIngredients.appendChild(tagItem);


      // a
      tag = doc.createElement("qty");
      tagItem.appendChild(tag);

      tag.appendChild(doc.createTextNode(QString::number(item.qty)));

      // b
      tag = doc.createElement("unit");
      tagItem.appendChild(tag);

      tag.appendChild(doc.createTextNode(units));

      // c
      tag = doc.createElement("descript");
      tagItem.appendChild(tag);

      tag.appendChild(doc.createTextNode(item.descript));
   }


   // 4
   tag = doc.createElement("directions");
   root.appendChild(tag);

   tag.appendChild(doc.createTextNode(m_rData.rDirections));

   // create a new stream, QDomNode writes the XML doc to the stream,
   // then the stream is automatically saved to the xml file
   QTextStream fOut(&file);
   doc.save(fOut, 3);

   file.close();
   QMessageBox::information( 0, "Export Recipe", "Xml file saved successfully.");

}

void R_Xml::importXml()

   // walk nodes
   QDomNode node = root.firstChild();
   QString data;

   while(! node.isNull()) {

     // convert the node to an element
     QDomElement element = node.toElement();

     if(! element.isNull()) {
        data = element.tagName();

        if (data == "rName") {
           m_rData.rName = element.text();


        } else if (data == "submitBy")  {
           m_rData.rSubmitBy = element.text();


        } else if (data == "categories") {
           m_rData.rRecipeKind = element.text();


        } else if (data == "ingredients") {
            parseIngredients(element);


        } else if (data == "directions") {
           m_rData.rDirections = element.text();

        }
     }

     node = node.nextSibling();
   }

   // test for duplicate
   bool isDup;
   isDup = this->m_sqlDb->testImport(m_rData.rName);

   while (isDup) {
      // get new recipe name from user

      PopUp_getRname *oDw = new PopUp_getRname(0, m_rData.rName);
      oDw->exec();

      int msgResponse = oDw->result();

      if (msgResponse == 1)  {
         m_rData.rName = oDw->getNewName();
         isDup = false;

      } else {
         // abort
         break;
      }

      // test again
      isDup = this->m_sqlDb->testImport(m_rData.rName);
   }

   if (isDup) {
      QMessageBox::information( 0, "Import Recipe", "Process aborted.");

   } else {           

      this->m_sqlDb->saveImport(m_rData, m_itemList);

      // send the signal to update the browser
      this->m_owner->emitSignal(1, m_rData.rRecipeKind);

      QMessageBox::information( 0, "Import Recipe", "New Recipe has been imported successfully.");
   }

}

void R_Xml::parseIngredients(QDomElement root)
{
   // walk ingredient nodes
   QDomNode node = root.firstChild();

   QString data;

   while(! node.isNull()) {
      // convert the node to an element
      QDomElement element = node.toElement();

      if(! element.isNull()) {

         // start of next ingredient
         if (element.tagName() == "item") {

            // new ingredient
            struct ingredientList item;

            //
            QDomNode node2 = element.firstChild();

            while(! node2.isNull()) {
               // convert item node to an element
               QDomElement pieces = node2.toElement();

               if(! pieces.isNull()) {
                  data = pieces.tagName();

                  if (data == "qty") {
                     item.qty = pieces.text().toDouble();

                  } else if (data == "unit")  {
                     item.unitName = pieces.text();

                  } else if (data == "descript")  {
                     item.descript = pieces.text();

                  }
               }

               node2 = node2.nextSibling();
            }

            // append struc to list
            m_itemList.append(item);

            //

         }

         // next ingredient
         node = node.nextSibling();
      }
   }

}

void MainWindow::saveAs()
{

    QString fileName =
            QFileDialog::getSaveFileName(this, tr("Save Bookmark File"),
                                         QDir::currentPath(),
                                         tr("XBEL Files (*.xbel *.xml)"));
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("SAX Bookmarks"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }

    if (xbelTree->write(&file))
        statusBar()->showMessage(tr("File saved"), 2000);
}


*/

