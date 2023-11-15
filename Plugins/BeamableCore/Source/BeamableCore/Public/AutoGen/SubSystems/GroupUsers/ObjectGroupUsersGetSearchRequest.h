
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"


#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt64.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt32.h"
#include "BeamableCore/Public/AutoGen/Enums/GroupType.h"
#include "BeamableCore/Public/AutoGen/GroupSearchResponse.h"

#include "ObjectGroupUsersGetSearchRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UObjectGroupUsersGetSearchRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId = {};
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name", Category="Beam")
	FOptionalString Name = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Score Min", Category="Beam")
	FOptionalInt64 ScoreMin = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Sort Field", Category="Beam")
	FOptionalString SortField = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="User Score", Category="Beam")
	FOptionalInt64 UserScore = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Has Slots", Category="Beam")
	FOptionalBool bHasSlots = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Enrollment Types", Category="Beam")
	FOptionalString EnrollmentTypes = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Offset", Category="Beam")
	FOptionalInt32 Offset = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Score Max", Category="Beam")
	FOptionalInt64 ScoreMax = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Sub Group", Category="Beam")
	FOptionalBool bSubGroup = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Sort Value", Category="Beam")
	FOptionalInt32 SortValue = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Type", Category="Beam")
	EGroupType Type = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Limit", Category="Beam")
	FOptionalInt32 Limit = {};

	// Body Params
	

	// Beam Base Request Declaration
	UObjectGroupUsersGetSearchRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|GroupUsers", DisplayName="Beam - Make ObjectGroupUsersGetSearch",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Name,_ScoreMin,_SortField,_UserScore,_bHasSlots,_EnrollmentTypes,_Offset,_ScoreMax,_bSubGroup,_SortValue,_Limit,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UObjectGroupUsersGetSearchRequest* Make(int64 _ObjectId, FOptionalString _Name, FOptionalInt64 _ScoreMin, FOptionalString _SortField, FOptionalInt64 _UserScore, FOptionalBool _bHasSlots, FOptionalString _EnrollmentTypes, FOptionalInt32 _Offset, FOptionalInt64 _ScoreMax, FOptionalBool _bSubGroup, FOptionalInt32 _SortValue, EGroupType _Type, FOptionalInt32 _Limit, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectGroupUsersGetSearchSuccess, FBeamRequestContext, Context, UObjectGroupUsersGetSearchRequest*, Request, UGroupSearchResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectGroupUsersGetSearchError, FBeamRequestContext, Context, UObjectGroupUsersGetSearchRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnObjectGroupUsersGetSearchComplete, FBeamRequestContext, Context, UObjectGroupUsersGetSearchRequest*, Request);

using FObjectGroupUsersGetSearchFullResponse = FBeamFullResponse<UObjectGroupUsersGetSearchRequest*, UGroupSearchResponse*>;
DECLARE_DELEGATE_OneParam(FOnObjectGroupUsersGetSearchFullResponse, FObjectGroupUsersGetSearchFullResponse);
