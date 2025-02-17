#include <algorithm>
using std::min;
using std::max;

#define _WIN32_WINNT _WIN32_WINNT_WIN7
#include <afx.h>

#include <QSettings>

#include <ZExcept.h>
#include <Ztrace.h>

#include "ResultParameters.h"
#include "ui/ui_ResultParameters.h"

#include "DSSCommon.h"
#include "StackSettings.h"
#include "Workspace.h"


ResultParameters::ResultParameters(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ResultParameters),
	workspace(new Workspace()),
	pStackSettings(dynamic_cast<StackSettings *>(parent))
{
	if (nullptr == pStackSettings)
	{
		delete ui;
		ZASSERTSTATE(nullptr != pStackSettings);
	}
	
    ui->setupUi(this);

}

ResultParameters::~ResultParameters()
{
    delete ui;
}

void ResultParameters::onSetActive()
{
	//
	// Initially set the Custom Rectangle radio buttion to disabled - it should only be enabled if
	// a custom rectangle has been defined and we are going to stack after registering.
	//
	ui->customMode->setEnabled(false);

	//
	// select the appropriate check box for stacking mode
	//
	STACKINGMODE stackingMode = static_cast<STACKINGMODE>(workspace->value("Stacking/Mosaic", uint(0)).toUInt());

	switch (stackingMode)
	{
	case SM_NORMAL:
		//
		// Custom rectangle mode is actually Normal Mode but with a custom rectangle
		// selected in this dialog.
		//
		// Its is only possible to do this if a custom rectangle has been defined which
		// should set customRectangleEnabled in the StackSettings class.
		//
		// If this has been done it is valid to select the custom rectangle stacking mode
		// so the radio button to select it can be enabled.
		//
		// If the user has previously selected to actually use custom rectangle mode by
		// clicking on the custom mode radio button in this dialog, we will make sure we 
		// select the button as we initialise and choose the appropiate picture and text.
		//
		if (pStackSettings->isCustomRectangleEnabled())
		{
			ui->customMode->setEnabled(true);
			if (pStackSettings->isCustomRectangleSelected())
			{
				ui->customMode->setChecked(true);
				if (customPix.isNull())
				{
					customPix.load(":/stacking/custommode.bmp");
				}
				ui->previewImage->setPixmap(customPix);
				ui->modeText->setText("");
			}
		}
		else
		{
			ui->normalMode->setChecked(true);
			if (normalPix.isNull())
			{
				normalPix.load(":/stacking/normalmode.bmp");
			}
			ui->previewImage->setPixmap(normalPix);
			ui->modeText->setText(tr("The result of the stacking process is framed by the reference light frame.",
				"IDS_STACKINGMODE_NORMAL"));
		}
		break;
	case SM_MOSAIC:
		ui->mosaicMode->setChecked(true);
		if (mosaicPix.isNull())
		{
			mosaicPix.load(":/stacking/mosaicmode.bmp");
		}
		ui->previewImage->setPixmap(mosaicPix);
		ui->modeText->setText(tr("The result of the stacking process contains all the light frames of the stack.",
			"IDS_STACKINGMODE_MOSAIC"));
		break;
	case SM_CUSTOM:
	case SM_INTERSECTION:
		ui->intersectionMode->setChecked(true);
		if (intersectionPix.isNull())
		{
			intersectionPix.load(":/stacking/intersectionmode.bmp");
		}
		ui->previewImage->setPixmap(intersectionPix);
		ui->modeText->setText(tr("The result of the stacking process is framed by the intersection of all the frames.",
			"IDS_STACKINGMODE_INTERSECTION"));
		break;
	default:
		break;
	}

	uint drizzle = workspace->value("Stacking/PixelSizeMultiplier", uint(0)).toUInt();
	switch (drizzle)
	{
	case 2:
		ui->drizzle2x->setChecked(true);
		break;
	case 3:
		ui->drizzle3x->setChecked(true);
		break;
	default:
		break;
	}

	bool alignRGB = workspace->value("Stacking/AlignChannels", false).toBool();
	ui->alignRGB->setChecked(alignRGB);
}

void	ResultParameters::on_normalMode_clicked()
{
	workspace->setValue("Stacking/Mosaic", (uint)SM_NORMAL);
	pStackSettings->selectCustomRectangle(false);
	if (normalPix.isNull())
	{
		normalPix.load(":/stacking/normalmode.bmp");
	}
	ui->previewImage->setPixmap(normalPix);
	ui->modeText->setText(tr("The result of the stacking process is framed by the reference light frame.",
		"IDS_STACKINGMODE_NORMAL"));
}

void	ResultParameters::on_mosaicMode_clicked()
{
	workspace->setValue("Stacking/Mosaic", (uint)SM_MOSAIC);
	pStackSettings->selectCustomRectangle(false);
	if (mosaicPix.isNull())
	{
		mosaicPix.load(":/stacking/mosaicmode.bmp");
	}
	ui->previewImage->setPixmap(mosaicPix);
	ui->modeText->setText(tr("The result of the stacking process contains all the light frames of the stack.",
		"IDS_STACKINGMODE_MOSAIC"));

}

void	ResultParameters::on_intersectionMode_clicked()
{
	workspace->setValue("Stacking/Mosaic", (uint)SM_INTERSECTION);
	pStackSettings->selectCustomRectangle(false);
	if (intersectionPix.isNull())
	{
		intersectionPix.load(":/stacking/intersectionmode.bmp");
	}
	ui->previewImage->setPixmap(intersectionPix);
	ui->modeText->setText(tr("The result of the stacking process is framed by the intersection of all the frames.",
		"IDS_STACKINGMODE_INTERSECTION"));
}

void	ResultParameters::on_customMode_clicked()
{
	//
	// SM_CUSTOM isn't used - instead we use normal stacking mode
	// and record the fact that a custom rectangle is being used
	// by calling a method on our parent dialog
	//
	workspace->setValue("Stacking/Mosaic", (uint)SM_NORMAL);
	pStackSettings->selectCustomRectangle(true);
	if (customPix.isNull())
	{
		customPix.load(":/stacking/custommode.bmp");
	}
	ui->previewImage->setPixmap(customPix);
	ui->modeText->setText("");
}

void	ResultParameters::on_drizzle2x_clicked()
{
	if (ui->drizzle2x->isChecked())
	{
		ui->drizzle3x->setChecked(false);
		workspace->setValue("Stacking/PixelSizeMultiplier", uint(2));
	}
	else
		workspace->setValue("Stacking/PixelSizeMultiplier", uint(1));
}

void	ResultParameters::on_drizzle3x_clicked()
{
	if (ui->drizzle3x->isChecked())
	{
		ui->drizzle2x->setChecked(false);
		workspace->setValue("Stacking/PixelSizeMultiplier", uint(3));
	}
	else
		workspace->setValue("Stacking/PixelSizeMultiplier", uint(1));
}

void	ResultParameters::on_alignRGB_clicked()
{
	if (ui->alignRGB->isChecked())
	{
		workspace->setValue("Stacking/AlignChannels", true);
	}
	else
	{
		workspace->setValue("Stacking/AlignChannels", false);
	}
}
