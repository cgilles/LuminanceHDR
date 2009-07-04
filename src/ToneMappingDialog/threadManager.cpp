/**
 * This file is a part of Qtpfsgui package.
 * ----------------------------------------------------------------------
 * Copyright (C) 2009 Franco Comida
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * ----------------------------------------------------------------------
 *
 * @author Franco Comida <fcomida@users.sourceforge.net>
 */

#include "threadManager.h"
#include "../Common/global.h"

ThreadManager::~ThreadManager() {
	clearAll();
}

ThreadManager::ThreadManager(QWidget *parent) : QDialog(parent) {
	setupUi(this);
	connect(clearButton,SIGNAL(clicked()),this,SLOT(clearAll()));
}

void ThreadManager::addProgressIndicator(TmoProgressIndicator *pi) {
	verticalLayout->addWidget(pi);	
	widgets.append(pi);
}

void ThreadManager::clearAll() {
	foreach(TmoProgressIndicator *pi, widgets) {
		if (pi->isTerminated()) {
			verticalLayout->removeWidget(pi);
			delete pi;
			widgets.removeOne(pi);
		}
	}
}

void ThreadManager::showEvent(QShowEvent *) {
	//TODO; save pos and size instead
	restoreGeometry(settings.value("ThreadManagerGeometry").toByteArray());
}

void ThreadManager::hideEvent(QHideEvent *) {
	settings.setValue("ThreadManagerGeometry", saveGeometry());
}

void ThreadManager::closeEvent(QCloseEvent *event) {
	event->ignore();
}