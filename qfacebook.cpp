/* ************************************************************************
 * Copyright (c) 2014 GMaxera <gmaxera@gmail.com>                         *
 *                                                                        *
 * This file is part of QtFacebook                                        *
 *                                                                        *
 * QtFacebook is free software: you can redistribute it and/or modify     *
 * it under the terms of the GNU General Public License as published by   *
 * the Free Software Foundation, either version 3 of the License, or      *
 * (at your option) any later version.                                    *
 *                                                                        *
 * This program is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                   *
 * See the GNU General Public License for more details.                   *
 *                                                                        *
 * You should have received a copy of the GNU General Public License      *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.   *
 * ********************************************************************** */

#include "qfacebook.h"

QObject* QFacebook::qFacebookProvider(QQmlEngine *engine, QJSEngine *scriptEngine) {
	Q_UNUSED(engine)
	Q_UNUSED(scriptEngine)
	return QFacebook::instance();
}

QFacebook* QFacebook::instance() {
	static QFacebook* facebook = new QFacebook();
	return facebook;
}

QFacebook::QFacebook(QObject *parent )
	: QObject(parent) {
	initPlatformData();
	connect( qApp, SIGNAL(applicationStateChanged(Qt::ApplicationState)),
			 this, SLOT(onApplicationStateChanged(Qt::ApplicationState)) );
}

QString QFacebook::getAppID() {
	return appID;
}

QString QFacebook::getDisplayName() {
	return displayName;
}

bool QFacebook::getConnected() {
	return connected;
}

QStringList QFacebook::getRequestPermissions() {
	return requestPermissions;
}

QStringList QFacebook::getGrantedPermissions() {
	return grantedPermissions;
}

QFacebook::FacebookState QFacebook::getState() {
	return state;
}

void QFacebook::onFacebookStateChanged( int newstate ) {
	state = (FacebookState)newstate;
	connected = ( state == SessionOpen || state == SessionOpenTokenExtended );
	emit stateChanged( state );
	emit connectedChanged( connected );
}

bool QFacebook::isReadPermission( QString permission ) {
	// FIXME: Does not contains all permissions listed here:
	// https://developers.facebook.com/docs/facebook-login/permissions/v2.2
	static QStringList knowRead = QStringList()
		<< "public_profile"
		<< "user_friends"
		<< "email";
	return knowRead.contains( permission );
}

