/****************************************************************************
**
** Copyright 2019 neuromore co
** Contact: https://neuromore.com/contact
**
** Commercial License Usage
** Licensees holding valid commercial neuromore licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and neuromore. For licensing terms
** and conditions see https://neuromore.com/licensing. For further
** information use the contact form at https://neuromore.com/contact.
**
** neuromore Public License Usage
** Alternatively, this file may be used under the terms of the neuromore
** Public License version 1 as published by neuromore co with exceptions as 
** appearing in the file neuromore-class-exception.md included in the 
** packaging of this file. Please review the following information to 
** ensure the neuromore Public License requirements will be met: 
** https://neuromore.com/npl
**
****************************************************************************/

#ifndef __NEUROMORE_EXPERIENCEWIZARDWINDOW_H
#define __NEUROMORE_EXPERIENCEWIZARDWINDOW_H

// include required headers
#include <Core/StandardHeaders.h>
#include <Core/String.h>
#include <Core/Timer.h>
#include <Core/Json.h>
#include <Graph/EegDeviceNode.h>
#include <Graph/FrequencyBandNode.h>
#include <Graph/DeviceInputNode.h>
#include <Graph/ChannelSelectorNode.h>
#include <Graph/Classifier.h>
#include <Graph/GraphImporter.h>
#include <Experience.h>
#include "../Config.h"
#include <ImageButton.h>
#include <QLayout>
#include <QComboBox>
#include <QDialog>
#include <QTimer>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QListWidget>
#include <User.h>


// window to select and quick configure a classifier into an experience for a user
class ExperienceWizardWindow : public QDialog
{
   Q_OBJECT
   public:
      ExperienceWizardWindow(const User& user, QWidget* parent);
      virtual ~ExperienceWizardWindow();

   signals:
      void OnExperienceCreated(const User& user);

   private slots:
      void OnClassifierSelectIndexChanged(int index);
      void OnStateMachineSelectIndexChanged(int index);
      void OnExperienceTextChanged(const QString& text);
      void OnCreateClicked();
      void OnChannelSelectorListItemAdd();
      void OnChannelSelectorListItemDelete();

   private:
      void RequestFileHierarchy();
      void ProcessFolder(const Core::Json::Item& folder);
      void SyncNodes();
      void SyncUi();
      void SyncCreateButton();

      inline QString GetClassifierName()
      {
         const int IDX = mClassifierSelect.currentIndex();
         return IDX >= 0 ? mClassifierSelect.itemText(IDX) : "";
      }
      inline QString GetClassifierId()
      {
         const int IDX = mClassifierSelect.currentIndex();
         return IDX >= 0 ? mClassifierSelect.itemData(IDX).toString() : "";
      }
      inline QString GetStateMachineName()
      {
         const int IDX = mStateMachineSelect.currentIndex();
         return IDX >= 0 ? mStateMachineSelect.itemText(IDX) : "";
      }
      inline QString GetStateMachineId()
      {
         const int IDX = mStateMachineSelect.currentIndex();
         return IDX >= 0 ? mStateMachineSelect.itemData(IDX).toString() : "";
      }

      void ReadChannelSelectorRow(int idx);
      void GetNodeChannels(Node* n, Core::Array<Core::String>& out);
      void GetNodeChannels(Node* n, Core::Array<std::tuple<Core::String, Core::String>>& out);
      void GetDevicesElectrodes(Core::Array<Core::String>& out);
      void CreateChannelSelectorEditColumn(Node* node, QWidget* container);
      void CreateChannelSelectorListItem(QListWidget& list, const char* channel, const char* band);
      uint32 HasChannelSelectorListItem(QListWidget& list, const char* channel, const char* band);

   private:
      const User                      mUser;
      Core::String                    mFolderId;
      Core::Array<Node*>              mQuickConfigNodes;
      Core::Array<FrequencyBandNode*> mFrequencyBandNodes;
      DeviceInputNode*                mEegNode;
      ChannelSelectorNode*            mEegChannelSelector;
      Core::Array<const BciDevice*>   mEegDevices;
      Core::Array<const BciDevice*>   mEegDevicesRemoved;
      Core::Array<Core::String>       mChannelsUsed;
      GraphImporter           mGraphImporter;
      Classifier*             mClassifier;
      QVBoxLayout             mMainLayout;
      QHBoxLayout             mHeaderLayout;
      QVBoxLayout             mHeaderLeftLayout;
      QVBoxLayout             mHeaderRightLayout;
      QHBoxLayout             mUserLayout;
      QLabel                  mUserDesc;
      QLabel                  mUserLabel;
      QHBoxLayout             mClassifierLayout;
      QLabel                  mClassifierSelectDesc;
      QComboBox               mClassifierSelect;
      QHBoxLayout             mStateMachineLayout;
      QLabel                  mStateMachineSelectDesc;
      QComboBox               mStateMachineSelect;
      QHBoxLayout             mExperienceLayout;
      QLabel                  mExperienceDesc;
      QLineEdit               mExperienceEdit;
      QLabel                  mSupportedDevicesDesc;
      QListWidget             mSupportedDevicesList;
      QTableWidget            mTableWidget;
      QTableWidgetItem        mHeaderType;
      QTableWidgetItem        mHeaderName;
      QTableWidgetItem        mHeaderEdit;
      QPushButton             mCreateButton;
};

#endif
