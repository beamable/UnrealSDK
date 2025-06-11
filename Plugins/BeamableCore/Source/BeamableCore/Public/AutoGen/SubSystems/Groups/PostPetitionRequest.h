
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/GroupApplication.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "PostPetitionRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostPetitionRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UGroupApplication* Body = {};

	// Beam Base Request Declaration
	UPostPetitionRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Groups|Utils|Make/Break", DisplayName="Make PostPetition",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_SubGroup,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostPetitionRequest* Make(int64 _ObjectId, FOptionalInt64 _SubGroup, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostPetitionSuccess, FBeamRequestContext, Context, UPostPetitionRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostPetitionError, FBeamRequestContext, Context, UPostPetitionRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostPetitionComplete, FBeamRequestContext, Context, UPostPetitionRequest*, Request);

using FPostPetitionFullResponse = FBeamFullResponse<UPostPetitionRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostPetitionFullResponse, FPostPetitionFullResponse);
