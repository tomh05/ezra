#include "explainerpage.h"

ExplainerPage::ExplainerPage(QString title, QString _text, QString imagePath)
{
    text = _text;

    if (!title.isEmpty()) {
    setTitle(title);
    }

    QVBoxLayout *layout = new QVBoxLayout;

    if (!_text.isEmpty()) {
    QLabel *label = new QLabel(_text);
    label->setOpenExternalLinks(true);
    label->setWordWrap(true);
    label->setMargin(10);
    layout->addWidget(label);
    }


    if (!imagePath.isEmpty()) {
    QPixmap image;
    image.load(imagePath);
    image.setDevicePixelRatio(devicePixelRatio());

    QLabel * imageLabel = new QLabel();
    imageLabel->setPixmap(image.scaled(400*devicePixelRatio(),350*devicePixelRatio(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
    // set a scaled pixmap to a w x h window keeping its aspect ratio
    layout->addWidget(imageLabel);
    }

    setLayout(layout);
}

void ExplainerPage::setText(const QString &value)
{
    text = value;
}
