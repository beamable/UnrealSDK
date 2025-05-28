
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/GroupMembershipRequestBody.h"
#include "BeamableCore/Public/AutoGen/GroupMembershipResponse.h"

#include "DeleteJoinRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteJoinRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UGroupMembershipRequestBody* Body = {};

	// Beam Base Request Declaration
	UDeleteJoinRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|GroupUsers|Utils|Make/Break", DisplayName="Make DeleteJoin",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Successor,_Score,_SubGroup,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UDeleteJoinRequest* Make(int64 _ObjectId, EBeamGroupType _Type, int64 _Group, FOptionalInt64 _Successor, FOptionalInt64 _Score, FOptionalInt64 _SubGroup, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteJoinSuccess, FBeamRequestContext, Context, UDeleteJoinRequest*, Request, UGroupMembershipResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteJoinError, FBeamRequestContext, Context, UDeleteJoinRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteJoinComplete, FBeamRequestContext, Context, UDeleteJoinRequest*, Request);

using FDeleteJoinFullResponse = FBeamFullResponse<UDeleteJoinRequest*, UGroupMembershipResponse*>;
DECLARE_DELEGATE_OneParam(FOnDeleteJoinFullResponse, FDeleteJoinFullResponse);
