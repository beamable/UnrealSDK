
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/SetContentRequestBody.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "PutContentRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutContentRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	FString ObjectId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	USetContentRequestBody* Body = {};

	// Beam Base Request Declaration
	UPutContentRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Events|Utils|Make/Break", DisplayName="Make PutContent",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_RootEventId,_OriginType,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutContentRequest* Make(FString _ObjectId, UEvent* _Event, FString _Origin, FOptionalString _RootEventId, FOptionalString _OriginType, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutContentSuccess, FBeamRequestContext, Context, UPutContentRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutContentError, FBeamRequestContext, Context, UPutContentRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutContentComplete, FBeamRequestContext, Context, UPutContentRequest*, Request);

using FPutContentFullResponse = FBeamFullResponse<UPutContentRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutContentFullResponse, FPutContentFullResponse);
