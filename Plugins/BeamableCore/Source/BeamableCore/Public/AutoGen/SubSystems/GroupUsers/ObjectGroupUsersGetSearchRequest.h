
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/Optionals/OptionalInt64.h"
#include "AutoGen/Optionals/OptionalBool.h"
#include "AutoGen/Optionals/OptionalInt32.h"

#include "AutoGen/GroupSearchResponse.h"

#include "ObjectGroupUsersGetSearchRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UObjectGroupUsersGetSearchRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name")
	FOptionalString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Score Min")
	FOptionalInt64 ScoreMin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Sort Field")
	FOptionalString SortField;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="User Score")
	FOptionalInt64 UserScore;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Has Slots")
	FOptionalBool bHasSlots;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Enrollment Types")
	FOptionalString EnrollmentTypes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Offset")
	FOptionalInt32 Offset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Score Max")
	FOptionalInt64 ScoreMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Sub Group")
	FOptionalBool bSubGroup;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Sort Value")
	FOptionalInt32 SortValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Type")
	TMap<FString, FString> Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Limit")
	FOptionalInt32 Limit;

	// Body Params
	

	// Beam Base Request Declaration
	UObjectGroupUsersGetSearchRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_Name,_ScoreMin,_SortField,_UserScore,_bHasSlots,_EnrollmentTypes,_Offset,_ScoreMax,_bSubGroup,_SortValue,_Limit,Outer"))
	static UObjectGroupUsersGetSearchRequest* MakeObjectGroupUsersGetSearchRequest(int64 _ObjectId, FOptionalString _Name, FOptionalInt64 _ScoreMin, FOptionalString _SortField, FOptionalInt64 _UserScore, FOptionalBool _bHasSlots, FOptionalString _EnrollmentTypes, FOptionalInt32 _Offset, FOptionalInt64 _ScoreMax, FOptionalBool _bSubGroup, FOptionalInt32 _SortValue, TMap<FString, FString> _Type, FOptionalInt32 _Limit, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectGroupUsersGetSearchSuccess, FBeamRequestContext, Context, UObjectGroupUsersGetSearchRequest*, Request, UGroupSearchResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectGroupUsersGetSearchError, FBeamRequestContext, Context, UObjectGroupUsersGetSearchRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnObjectGroupUsersGetSearchComplete, FBeamRequestContext, Context, UObjectGroupUsersGetSearchRequest*, Request);

using FObjectGroupUsersGetSearchFullResponse = FBeamFullResponse<UObjectGroupUsersGetSearchRequest*, UGroupSearchResponse*>;
DECLARE_DELEGATE_OneParam(FOnObjectGroupUsersGetSearchFullResponse, FObjectGroupUsersGetSearchFullResponse);
