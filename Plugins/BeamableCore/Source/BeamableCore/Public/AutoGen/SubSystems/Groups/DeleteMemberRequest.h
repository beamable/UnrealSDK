
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/KickRequestBody.h"
#include "BeamableCore/Public/AutoGen/GroupMembershipResponse.h"

#include "DeleteMemberRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteMemberRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UKickRequestBody* Body = {};

	// Beam Base Request Declaration
	UDeleteMemberRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Groups|Utils|Make/Break", DisplayName="Make DeleteMember",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_SubGroup,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UDeleteMemberRequest* Make(int64 _ObjectId, int64 _GamerTag, FOptionalInt64 _SubGroup, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteMemberSuccess, FBeamRequestContext, Context, UDeleteMemberRequest*, Request, UGroupMembershipResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteMemberError, FBeamRequestContext, Context, UDeleteMemberRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteMemberComplete, FBeamRequestContext, Context, UDeleteMemberRequest*, Request);

using FDeleteMemberFullResponse = FBeamFullResponse<UDeleteMemberRequest*, UGroupMembershipResponse*>;
DECLARE_DELEGATE_OneParam(FOnDeleteMemberFullResponse, FDeleteMemberFullResponse);
