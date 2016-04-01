%bcond_with x
%bcond_with wayland

Name: dpm-toolkit
Summary: Tizen DPM Test package
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

%if %{with x}
BuildRequires: pkgconfig(x11)
%endif

%description
Device Policy Manager test pakcage

%prep
%setup -q

%build
cmake . -DCMAKE_INSTALL_PREFIX="%{TZ_SYS_RO_APP}" \
       -DCMAKE_DESKTOP_ICON_DIR="%{TZ_SYS_RW_ICONS}/default/small" \
       -DCMAKE_APP_SHARE_PACKAGES_DIR="%{TZ_SYS_RO_PACKAGES}" \
%if %{with wayland} && !%{with x}
-Dwith_wayland=TRUE
%else
-Dwith_x=TRUE
%endif

make %{?jobs:-j%jobs}

%install
%make_install

#for package signing step
#%define signature_list %{TZ_USER_APP}/org.tizen.test-app;
#%define tizen_sign 1
#%define tizen_sign_base %{signature_list}
#%define tizen_sign_level platform
#%define tizen_author_sign 1
#%define tizen_dist_sign 1

#mkdir -p %{buildroot}/%{_datadir}/packages/
#cp %{_builddir}/%{buildsubdir}/org.tizen.dpm-util.xml %{buildroot}/%{_datadir}/packages/org.tizen.dpm-util.xml

%package -n org.tizen.dpm-toolkit
Summary: DPM test application
Group: Security/Other

Requires: %{name} = %{version}-%{release}

%description -n org.tizen.dpm-toolkit
DPM test application

%post -n org.tizen.dpm-toolkit
/sbin/ldconfig

%postun -n org.tizen.dpm-toolkit
/sbin/ldconfig

%files -n org.tizen.dpm-toolkit
%manifest test-app/org.tizen.dpm-toolkit.manifest
%defattr(-,root,root,-)
%{TZ_SYS_RO_APP}/org.tizen.dpm-toolkit/bin/*
%{TZ_SYS_RO_APP}/org.tizen.dpm-toolkit/test.xml
%{TZ_SYS_RO_PACKAGES}/org.tizen.dpm-toolkit.xml
%{TZ_SYS_RW_ICONS}/default/small/org.tizen.dpm-toolkit.png

