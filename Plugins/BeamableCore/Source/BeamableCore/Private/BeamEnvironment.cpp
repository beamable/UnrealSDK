// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamEnvironment.h"

#include "BeamCoreSettings.h"
#include "Engine/AssetManager.h"

const FString RUNTIME_BEAM_ENVIRONMENT = FString::Printf(TEXT("BeamEnvironmentData:Runtime"));
const FString EDITOR_BEAM_ENVIRONMENT = FString::Printf(TEXT("BeamEnvironmentData:Editor"));


void UBeamEnvironmentData::Serialize(FJsonSerializerBase& Serializer, bool bFlatObject)
{
	Serializer.StartObject();
	Serializer.Serialize(TEXT("host"), APIUrl);
	Serializer.EndObject();
}

void UBeamEnvironment::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UBeamEnvironment::Deinitialize()
{
}

FString UBeamEnvironment::GetAPIUrl()
{
	if (!Data)
	{
		const UBeamCoreSettings* beamCoreSettings = GetDefault<UBeamCoreSettings>();		
		Data = beamCoreSettings->BeamableEnvironment.LoadSynchronous();
	}

	return Data->APIUrl;
}


const FString FBeamPackageVersion::PREVIEW_STRING = FString::Printf(TEXT("PREVIEW"));
const FString FBeamPackageVersion::RC_STRING = FString::Printf(TEXT("RC"));
const FString FBeamPackageVersion::NIGHTLY_STRING = FString::Printf(TEXT("NIGHTLY"));


const int FBeamPackageVersion::UNASSIGNED_VALUE = -1;
const char FBeamPackageVersion::VERSION_SEPARATOR = '.';
const char FBeamPackageVersion::PREVIEW_SEPARATOR = '-';

FBeamPackageVersion::FBeamPackageVersion()
{
}

FBeamPackageVersion::FBeamPackageVersion(int major, int minor, int patch, int rc, long nightlyTime, bool isPreview)
{
	Major = major;
	Minor = minor;
	Patch = patch;
	RC = rc;
	NightlyTime = nightlyTime;
	bIsPreview = isPreview;
}

FBeamPackageVersion::FBeamPackageVersion(const FString& VersionString)
{
	*this = FromString(VersionString);
}

bool FBeamPackageVersion::Equals(const FBeamPackageVersion Other) const
{
	return Major == Other.Major && Minor == Other.Minor && Patch == Other.Patch && RC == Other.RC && NightlyTime == Other.NightlyTime && bIsPreview == Other.bIsPreview;
}

inline bool FBeamPackageVersion::operator<(const FBeamPackageVersion& BeamPackageVersion) const
{
	return this->Major < BeamPackageVersion.Major ||
		(this->Major <= BeamPackageVersion.Major && this->Minor < BeamPackageVersion.Minor) ||
		(this->Major <= BeamPackageVersion.Minor && this->Minor <= BeamPackageVersion.Minor && (this->Patch < BeamPackageVersion.Patch));
}

inline bool FBeamPackageVersion::operator>(const FBeamPackageVersion& BeamPackageVersion) const
{
	return BeamPackageVersion.Major < this->Major ||
		(BeamPackageVersion.Major <= this->Major && BeamPackageVersion.Minor < this->Minor) ||
		(BeamPackageVersion.Major <= this->Minor && BeamPackageVersion.Minor <= this->Minor && (BeamPackageVersion.Patch < this->Patch));
}

inline bool FBeamPackageVersion::operator==(const FBeamPackageVersion& BeamPackageVersion) const
{
	return this->Equals(BeamPackageVersion);
}

inline bool FBeamPackageVersion::operator!=(const FBeamPackageVersion& BeamPackageVersion) const
{
	return !(*this == BeamPackageVersion);
}

inline bool FBeamPackageVersion::operator<=(const FBeamPackageVersion& BeamPackageVersion) const
{
	return *this < BeamPackageVersion || *this == BeamPackageVersion;
}

inline bool FBeamPackageVersion::operator>=(const FBeamPackageVersion& BeamPackageVersion) const
{
	return *this > BeamPackageVersion || *this == BeamPackageVersion;
}

FString FBeamPackageVersion::ToString() const
{
	auto sb = FString();
	sb.Reserve(64);
	sb.AppendInt(Major);
	sb.AppendChar(VERSION_SEPARATOR);
	sb.AppendInt(Minor);
	sb.AppendChar(VERSION_SEPARATOR);
	sb.AppendInt(Patch);
	if (bIsPreview)
	{
		sb.AppendChar(PREVIEW_SEPARATOR);
		sb.Append(PREVIEW_STRING);
	}

	if (IsNightly())
	{
		sb.AppendChar(VERSION_SEPARATOR);
		sb.Append(NIGHTLY_STRING);
		sb.AppendChar(PREVIEW_SEPARATOR);
		sb.Append(FString::Printf(TEXT("%lld"), NightlyTime));
	}

	if (IsReleaseCandidate())
	{
		sb.AppendChar(VERSION_SEPARATOR);
		sb.Append(RC_STRING);
		sb.AppendInt(RC);
	}

	return sb;
}

FBeamPackageVersion FBeamPackageVersion::FromString(FString SemanticVersion)
{
	auto major = -1;
	auto minor = -1;
	auto patch = -1;
	auto rc = -1;
	auto nightlyTime = -1L;
	auto isPreview = false;

	auto buffer = FString("");
	for (auto i = 0; i < GetNum(SemanticVersion); i++)
	{
		auto c = SemanticVersion[i];
		if (!isPreview && buffer.Equals(PREVIEW_STRING))
		{
			isPreview = true;
			buffer = "";
		}

		auto bufferCharArray = *buffer;
		if (buffer.Equals(RC_STRING))
		{
			ensureAlways(FCString::IsNumeric(bufferCharArray));
			rc = FCString::Atoi(bufferCharArray);
			break;
		}

		if (buffer.Equals(NIGHTLY_STRING))
		{
			// add one to ignore the expected - character
			ensureAlways(FCString::IsNumeric(bufferCharArray));
			nightlyTime = FCString::Atoi64(bufferCharArray);
			break;
		}

		if (c == VERSION_SEPARATOR && major == UNASSIGNED_VALUE)
		{
			ensureAlways(FCString::IsNumeric(bufferCharArray));
			major = FCString::Atoi(bufferCharArray);
			buffer.Reset();
		}
		else if (c == VERSION_SEPARATOR && minor == UNASSIGNED_VALUE)
		{
			ensureAlways(FCString::IsNumeric(bufferCharArray));
			minor = FCString::Atoi(bufferCharArray);
			buffer.Reset();
		}
		else if (c == PREVIEW_SEPARATOR && patch == UNASSIGNED_VALUE)
		{
			ensureAlways(FCString::IsNumeric(bufferCharArray));
			patch = FCString::Atoi(bufferCharArray);
			buffer.Reset();
		}
		else if (c == PREVIEW_SEPARATOR || c == VERSION_SEPARATOR)
		{
			// Do nothing here	
		}
		else
		{
			buffer.AppendChar(c);
		}


		auto bLastChar = i == GetNum(SemanticVersion) - 1;
		if (bLastChar && patch == UNASSIGNED_VALUE)
		{
			ensureAlways(FCString::IsNumeric(bufferCharArray));
			patch = FCString::Atoi(bufferCharArray);
		}
	}

	return FBeamPackageVersion(major, minor, patch, rc, nightlyTime, isPreview);
}
