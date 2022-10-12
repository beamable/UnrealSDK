
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/GroupCreate.h"
#include "AutoGen/GroupCreateResponse.h"

#include "PostGroupRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostGroupRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UGroupCreate* Body;

	// Beam Base Request Declaration
	UPostGroupRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_Tag,_ClientData,_Scores,_Time,_Group,Outer"))
	static UPostGroupRequest* MakePostGroupRequest(int64 _ObjectId, FString _Name, FString _EnrollmentType, FOptionalString _Tag, int64 _Requirement, FOptionalString _ClientData, FOptionalArrayOfGroupScoreBinding _Scores, FOptionalInt32 _Time, EGroupType _Type, int32 _MaxSize, FOptionalInt64 _Group, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostGroupSuccess, FBeamRequestContext, Context, UPostGroupRequest*, Request, UGroupCreateResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostGroupError, FBeamRequestContext, Context, UPostGroupRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostGroupComplete, FBeamRequestContext, Context, UPostGroupRequest*, Request);

using FPostGroupFullResponse = FBeamFullResponse<UPostGroupRequest*, UGroupCreateResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostGroupFullResponse, FPostGroupFullResponse);
