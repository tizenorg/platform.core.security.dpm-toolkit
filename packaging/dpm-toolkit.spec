Name: org.tizen.dpm-toolkit
Summary: Tizen DPM test toolkit package
Version: 0.1
Release: 0
ExclusiveArch: %arm
Group: Security/Other
License: Apache-2.0
Source0: %{name}-%{version}.tar.gz

BuildRequires: gcc
BuildRequires: cmake
BuildRequires: pkgconfig(glib-2.0)
BuildRequires: pkgconfig(elementary)
BuildRequires: pkgconfig(dlog)
BuildRequires: pkgconfig(capi-appfw-application)
BuildRequires: pkgconfig(efl-extension)
BuildRequires: pkgconfig(libxml-2.0)
BuildRequires: pkgconfig(capi-system-system-settings)
BuildRequires: pkgconfig(evas)
BuildRequires: pkgconfig(dpm)

%description
Device Policy Manager test toolkit pakcage

%prep
%setup -q

%build
%{!?profile:%define profile "mobile"}

cmake . -DCMAKE_INSTALL_PREFIX="%{TZ_SYS_RO_APP}" \
        -DCMAKE_DESKTOP_ICON_DIR="%{TZ_SYS_RW_ICONS}/default/small" \
        -DCMAKE_APP_SHARE_PACKAGES_DIR="%{TZ_SYS_RO_PACKAGES}" \
        -DTIZEN_PROFILE_NAME=%{profile}

make %{?jobs:-j%jobs}

%install
%make_install

%post
/sbin/ldconfig
cp %{TZ_SYS_RO_APP}/org.tizen.dpm-toolkit/sampleapp.tpk /opt/data/dpm/
ln -sf %{TZ_SYS_RO_APP}/org.tizen.dpm-toolkit/bin/org.tizen.dpm-toolkit /usr/bin/dpm-admin-cli

%postun
/sbin/ldconfig

%files
%manifest org.tizen.dpm-toolkit.manifest
%defattr(-,root,root,-)
%{TZ_SYS_RO_APP}/org.tizen.dpm-toolkit/bin/*
%{TZ_SYS_RO_APP}/org.tizen.dpm-toolkit/res/*
%{TZ_SYS_RO_APP}/org.tizen.dpm-toolkit/test.xml
%{TZ_SYS_RO_APP}/org.tizen.dpm-toolkit/sampleapp.tpk
%{TZ_SYS_RO_PACKAGES}/org.tizen.dpm-toolkit.xml
%{TZ_SYS_RW_ICONS}/default/small/org.tizen.dpm-toolkit.png
