
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/GroupMembershipRequestBody.h"
#include "AutoGen/GroupMembershipResponse.h"

#include "DeleteJoinRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteJoinRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UGroupMembershipRequestBody* Body;

	// Beam Base Request Declaration
	UDeleteJoinRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_Successor,_Score,_SubGroup,Outer"))
	static UDeleteJoinRequest* MakeDeleteJoinRequest(int64 _ObjectId, FOptionalInt64 _Successor, FOptionalInt64 _Score, FOptionalInt64 _SubGroup, EGroupType _Type, int64 _Group, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteJoinSuccess, FBeamRequestContext, Context, UDeleteJoinRequest*, Request, UGroupMembershipResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteJoinError, FBeamRequestContext, Context, UDeleteJoinRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteJoinComplete, FBeamRequestContext, Context, UDeleteJoinRequest*, Request);

using FDeleteJoinFullResponse = FBeamFullResponse<UDeleteJoinRequest*, UGroupMembershipResponse*>;
DECLARE_DELEGATE_OneParam(FOnDeleteJoinFullResponse, FDeleteJoinFullResponse);
