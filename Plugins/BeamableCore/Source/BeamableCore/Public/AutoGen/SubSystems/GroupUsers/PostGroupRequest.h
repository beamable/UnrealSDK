
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"


#include "AutoGen/GroupCreate.h"
#include "AutoGen/GroupCreateResponse.h"

#include "PostGroupRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostGroupRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UGroupCreate* Body;

	// Beam Base Request Declaration
	UPostGroupRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|GroupUsers", DisplayName="Beam - Make PostGroup",  meta=(DefaultToSelf="Outer", AdvancedDisplay="_Tag,_ClientData,_Time,_Group,_Scores,Outer"))
	static UPostGroupRequest* Make(int64 _ObjectId, FString _Name, FString _EnrollmentType, int64 _Requirement, EGroupType _Type, int32 _MaxSize, FOptionalString _Tag, FOptionalString _ClientData, FOptionalInt32 _Time, FOptionalInt64 _Group, FOptionalArrayOfGroupScoreBinding _Scores, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostGroupSuccess, FBeamRequestContext, Context, UPostGroupRequest*, Request, UGroupCreateResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostGroupError, FBeamRequestContext, Context, UPostGroupRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostGroupComplete, FBeamRequestContext, Context, UPostGroupRequest*, Request);

using FPostGroupFullResponse = FBeamFullResponse<UPostGroupRequest*, UGroupCreateResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostGroupFullResponse, FPostGroupFullResponse);
