#
# spec file for package 
#
# Copyright (c) 2010 SUSE LINUX Products GmbH, Nuernberg, Germany.
#
# All modifications and additions to the file contributed by third parties
# remain the property of their copyright owners, unless otherwise agreed
# upon. The license for this file, and modifications and additions to the
# file, is the same license as for the pristine package itself (unless the
# license for the pristine package is not an Open Source License, in which
# case the license is the MIT License). An "Open Source License" is a
# license that conforms to the Open Source Definition (Version 1.9)
# published by the Open Source Initiative.

# Please submit bugfixes or comments via http://bugs.opensuse.org/
#

# norootforbuild

Name:           hello
Version:	0.0.1
Release:	1
License:	GPL
Summary:	hello - quick run
Url:		https://github.com/Airead/gnome-excise
Group:		Development/Tools/Other
Source:		https://github.com/Airead/gnome-excise/blob/master/tar/hello-0.0.1.tar.gz
BuildRequires:  gtk2-devel
BuildRoot:      %{_tmppath}/%{name}-%{version}-build

%description
A quick run app

%prep
%setup -q

%build
make

%install
rm -rf $RPM_BUILD_ROOT
mkdir $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/usr/bin
make DESTDIR=$RPM_BUILD_ROOT/usr/bin install

%clean
%{?buildroot:%__rm -rf "%{buildroot}"}

%files
%defattr(-,root,root)
/usr/bin
%doc README

%changelog

