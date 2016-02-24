#include "explainerpage.h"

ExplainerPage::ExplainerPage(QString title, QString text, QString imagePath)
{
    qDebug()<< title << text << imagePath;

    if (!title.isEmpty()) {
    setTitle(title);
    }

    QVBoxLayout *layout = new QVBoxLayout;

    if (!text.isEmpty()) {
    QLabel *label = new QLabel(text);
    label->setOpenExternalLinks(true);
    label->setWordWrap(true);
    label->setMargin(10);
    layout->addWidget(label);
    }


    if (!imagePath.isEmpty()) {
    QPixmap image;
    image.load(imagePath);

    QLabel * imageLabel = new QLabel();
    imageLabel->setPixmap(image.scaled(400,400,Qt::KeepAspectRatio,Qt::SmoothTransformation));
    // set a scaled pixmap to a w x h window keeping its aspect ratio
    layout->addWidget(imageLabel);
    }

    setLayout(layout);
}
