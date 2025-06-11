
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/PutLocalizationsRequestBody.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "PutLocalizationsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutLocalizationsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UPutLocalizationsRequestBody* Body = {};

	// Beam Base Request Declaration
	UPutLocalizationsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Content|Utils|Make/Break", DisplayName="Make PutLocalizations",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutLocalizationsRequest* Make(TMap<FString, FArrayOfLocalizedValue> _Localizations, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutLocalizationsSuccess, FBeamRequestContext, Context, UPutLocalizationsRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutLocalizationsError, FBeamRequestContext, Context, UPutLocalizationsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutLocalizationsComplete, FBeamRequestContext, Context, UPutLocalizationsRequest*, Request);

using FPutLocalizationsFullResponse = FBeamFullResponse<UPutLocalizationsRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutLocalizationsFullResponse, FPutLocalizationsFullResponse);
