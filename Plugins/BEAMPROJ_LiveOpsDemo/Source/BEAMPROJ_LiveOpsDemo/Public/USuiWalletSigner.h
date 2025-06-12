#pragma once

#include "CoreMinimal.h"
#include "Containers/Array.h"
#include "Containers/UnrealString.h"
#include "HAL/PlatformFilemanager.h"
#include "Misc/SecureHash.h"
#include "Engine/Engine.h"

// Note: You'll need to add these third-party libraries to your UE5 project
// Add to your .Build.cs file:
// PublicDependencyModuleNames.AddRange(new string[] { "libsodium" });
// Or use UE5's built-in crypto if available in your version

// For UE5 integration, we'll use platform-specific includes
#if PLATFORM_WINDOWS
#include "Windows/AllowWindowsPlatformTypes.h"
#include <compact25519.h>
#include <blake2.h>

#include "Windows/HideWindowsPlatformTypes.h"
#elif PLATFORM_MAC || PLATFORM_LINUX
    #include <compact25519.h>
#endif

#include "USuiWalletSigner.generated.h"

UCLASS(BlueprintType, Blueprintable)
class BEAMPROJ_LIVEOPSDEMO_API USuiWalletSigner : public UObject
{
	GENERATED_BODY()

private:
	// Use UE5's TArray instead of std::array
	TArray<uint8> PrivateKey;
	TArray<uint8> PublicKey;

	// Blake2b hash function using libsodium
	TArray<uint8> Blake2bHash(const TArray<uint8>& Data) const
	{
		TArray<uint8> Hash;
		Hash.SetNumUninitialized(32); // 256 bits = 32 bytes

		if (blake2b(Hash.GetData(), Hash.Num(),
		            Data.GetData(), Data.Num(),
		            nullptr, 0) != 0)
		{
			UE_LOG(LogTemp, Error, TEXT("Blake2b hashing failed"));
			Hash.Empty();
		}

		return Hash;
	}

	// Convert hex FString to bytes
	TArray<uint8> HexStringToBytes(const FString& HexString) const
	{
		TArray<uint8> Bytes;

		if (HexString.Len() % 2 != 0)
		{
			UE_LOG(LogTemp, Error, TEXT("Invalid hex string length"));
			return Bytes;
		}

		for (int32 i = 0; i < HexString.Len(); i += 2)
		{
			FString ByteString = HexString.Mid(i, 2);
			uint8 Byte = FCString::Strtoi(*ByteString, nullptr, 16);
			Bytes.Add(Byte);
		}

		return Bytes;
	}

	// Convert bytes to hex FString
	FString BytesToHexString(const TArray<uint8>& Bytes) const
	{
		FString HexString;
		for (uint8 Byte : Bytes)
		{
			HexString += FString::Printf(TEXT("%02x"), Byte);
		}
		return HexString;
	}

public:
	// Generate a new Ed25519 keypair
	UFUNCTION(BlueprintCallable, Category = "Sui Wallet")
	bool GenerateKeypair()
	{
		PrivateKey.SetNumUninitialized(64);
		PublicKey.SetNumUninitialized(32);
		TArray<uint8> Seed;

		for (int32 i = 0; i < 32; i++)
		{
			Seed.Add(FMath::RandRange(0, 255));
		}

		compact_ed25519_keygen(PrivateKey.GetData(), PublicKey.GetData(), Seed.GetData());
		UE_LOG(LogTemp, Display, TEXT("Private Key Generated: %s"), *BytesToHexString(PrivateKey));
		return true;
	}

	// Load private key from hex string
	UFUNCTION(BlueprintCallable, Category = "Sui Wallet")
	bool LoadPrivateKey(const FString& PrivateKeyHex)
	{
		if (PrivateKeyHex.Len() != 64)
		{
			UE_LOG(LogTemp, Error, TEXT("Private key must be 64 hex characters (32 bytes)"));
			return false;
		}

		TArray<uint8> KeyBytes = HexStringToBytes(PrivateKeyHex);
		if (KeyBytes.Num() != 32)
		{
			return false;
		}

		PrivateKey = KeyBytes;
		PublicKey.SetNumUninitialized(32);

		compact_ed25519_calc_public_key(PublicKey.GetData(), PrivateKey.GetData());

		return true;
	}

	// Get public key as hex string
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Sui Wallet")
	FString GetPublicKeyHex() const
	{
		if (PublicKey.Num() != 32)
		{
			UE_LOG(LogTemp, Warning, TEXT("Public key not available"));
			return FString();
		}

		return BytesToHexString(PublicKey);
	}

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Sui Wallet")
	FString GetPrivateKeyHex() const
	{
		return BytesToHexString(PrivateKey);
	}

	// Sign a message according to Sui's signing format
	UFUNCTION(BlueprintCallable, Category = "Sui Wallet")
	FString SignMessage(const FString& Message)
	{
		// Convert FString to UTF8 bytes
		FTCHARToUTF8 UTF8String(*Message);
		TArray<uint8> MessageBytes;
		MessageBytes.Append(reinterpret_cast<const uint8*>(UTF8String.Get()), UTF8String.Length());

		// Sui uses this domain separator for personal message signing
		const uint8 DomainSeparator = 0x03; // Intent::PersonalMessage

		// Create signing data: domain_separator + message_length + message
		TArray<uint8> SigningData;
		SigningData.Add(DomainSeparator);
		SigningData.Add(0x00);
		SigningData.Add(0x00);

		// Add message length as varint (simplified for messages < 127 bytes)
		if (MessageBytes.Num() < 127)
		{
			SigningData.Add(static_cast<uint8>(MessageBytes.Num()));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Message too long for this simplified implementation"));
			return FString();
		}


		// Add message bytes
		SigningData.Append(MessageBytes);

		// Hash the signing data with Blake2b
		TArray<uint8> MessageHash = Blake2bHash(SigningData);
		if (MessageHash.Num() != 32)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to hash message"));
			return FString();
		}

		// Sign the hash with Ed25519
		TArray<uint8> Signature;
		Signature.SetNumUninitialized(64);
		// UE_LOG(LogTemp, Display, TEXT("Signing message = %s"), *BytesToHexString(MessageHash));

		compact_ed25519_sign(Signature.GetData(), PrivateKey.GetData(),
		                     MessageHash.GetData(), MessageHash.Num());


		// Sui signature format: signature_bytes + public_key + signature_scheme_flag
		TArray<uint8> SuiSignature;

		SuiSignature.Add(0x00);

		// Add signature bytes (64 bytes for Ed25519)
		for (int32 i = 0; i < 64; ++i)
		{
			SuiSignature.Add(Signature[i]);
		}

		// Add public key (32 bytes)
		SuiSignature.Append(PublicKey);

		// Add signature scheme flag (0x00 for Ed25519)

		UE_LOG(LogTemp, Display, TEXT("Private Key = %s"), *BytesToHexString(PrivateKey));
		UE_LOG(LogTemp, Display, TEXT("Public Key = %s"), *BytesToHexString(PublicKey));
		UE_LOG(LogTemp, Display, TEXT("Message Challenge = %s"), *Message);
		UE_LOG(LogTemp, Display, TEXT("Message Bytes  = %s"), *BytesToHexString(MessageBytes));
		UE_LOG(LogTemp, Display, TEXT("Message Hash  = %s"), *BytesToHexString(MessageHash));
		UE_LOG(LogTemp, Display, TEXT("Raw Signature  = %s"), *BytesToHexString(Signature));
		UE_LOG(LogTemp, Display, TEXT("Signature Sui  = %s"), *BytesToHexString(SuiSignature));

		return BytesToHexString(SuiSignature);
	}

	// Verify a signature (for testing purposes)
	UFUNCTION(BlueprintCallable, Category = "Sui Wallet")
	bool VerifySignature(const FString& Message, const FString& SignatureHex) const
	{
		if (PublicKey.Num() != 32)
		{
			return false;
		}

		TArray<uint8> SignatureBytes = HexStringToBytes(SignatureHex);

		if (SignatureBytes.Num() != 97) // 64 + 32 + 1
		{
			UE_LOG(LogTemp, Warning, TEXT("Invalid signature length"));
			return false;
		}

		// Extract signature part (first 64 bytes)
		TArray<uint8> Signature;
		for (int32 i = 1; i < 65; ++i)
		{
			Signature.Add(SignatureBytes[i]);
		}

		// Recreate the signing data and hash
		FTCHARToUTF8 UTF8String(*Message);
		TArray<uint8> MessageBytes;
		MessageBytes.Append(reinterpret_cast<const uint8*>(UTF8String.Get()), UTF8String.Length());

		const uint8 DomainSeparator = 0x03;
		TArray<uint8> SigningData;
		SigningData.Add(DomainSeparator);
		SigningData.Add(0x00);
		SigningData.Add(0x00);
		SigningData.Add(static_cast<uint8>(MessageBytes.Num()));
		SigningData.Append(MessageBytes);

		TArray<uint8> MessageHash = Blake2bHash(SigningData);
		if (MessageHash.Num() != 32)
		{
			return false;
		}

		// Verify signature
		return compact_ed25519_verify(Signature.GetData(), PublicKey.GetData(),
		                              MessageHash.GetData(), MessageHash.Num());
	}

	// Blueprint-friendly version that logs results
	UFUNCTION(BlueprintCallable, Category = "Sui Wallet")
	void TestSigning()
	{
		UE_LOG(LogTemp, Warning, TEXT("=== Testing Sui Wallet Signing ==="));

		if (!GenerateKeypair())
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to generate keypair"));
			return;
		}

		UE_LOG(LogTemp, Warning, TEXT("Public Key: %s"), *GetPublicKeyHex());

		FString TestMessage = TEXT("Hello, Sui blockchain from UE5!");
		FString Signature = SignMessage(TestMessage);

		if (Signature.IsEmpty())
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to sign message"));
			return;
		}

		UE_LOG(LogTemp, Warning, TEXT("Message: %s"), *TestMessage);
		UE_LOG(LogTemp, Warning, TEXT("Signature: %s"), *Signature);

		bool bIsValid = VerifySignature(TestMessage, Signature);
		UE_LOG(LogTemp, Warning, TEXT("Signature Valid: %s"), bIsValid ? TEXT("Yes") : TEXT("No"));

		// Test with wrong message
		bool bIsInvalid = VerifySignature(TEXT("Wrong message"), Signature);
		UE_LOG(LogTemp, Warning, TEXT("Wrong Message Valid: %s"), bIsInvalid ? TEXT("Yes") : TEXT("No"));
	}
};

// Example usage in a Blueprint or C++ class
/*
// In your game class or component:

UCLASS()
class YOURGAME_API AMyActor : public AActor
{
    GENERATED_BODY()

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sui", meta = (AllowPrivateAccess = "true"))
    USuiWalletSigner* SuiSigner;

public:
    AMyActor()
    {
        PrimaryActorTick.bCanEverTick = false;
        SuiSigner = CreateDefaultSubobject<USuiWalletSigner>(TEXT("SuiSigner"));
    }

    UFUNCTION(BlueprintCallable, Category = "Sui")
    FString SignUserMessage(const FString& UserMessage)
    {
        if (!SuiSigner)
        {
            return FString();
        }
        
        // Generate keypair if not already done
        if (SuiSigner->GetPublicKeyHex().IsEmpty())
        {
            SuiSigner->GenerateKeypair();
        }
        
        return SuiSigner->SignMessage(UserMessage);
    }
};
*/

/*
Setup Instructions for UE5:

1. **Add libsodium to your project:**
   - Download libsodium from https://libsodium.org
   - Place the library files in your project's ThirdParty folder
   - Update your module's .Build.cs file:

   ```csharp
   public class YourGame : ModuleRules
   {
       public YourGame(ReadOnlyTargetRules Target) : base(Target)
       {
           PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
           
           PublicDependencyModuleNames.AddRange(new string[] { 
               "Core", 
               "CoreUObject", 
               "Engine" 
           });
           
           // Add libsodium
           if (Target.Platform == UnrealTargetPlatform.Win64)
           {
               PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "ThirdParty", "libsodium", "include"));
               PublicLibraryPaths.Add(Path.Combine(ModuleDirectory, "ThirdParty", "libsodium", "lib", "Win64"));
               PublicAdditionalLibraries.Add("libsodium.lib");
           }
           // Add similar blocks for Mac/Linux if needed
       }
   }
   ```

2. **Usage in Blueprints:**
   - Create a USuiWalletSigner object
   - Call GenerateKeypair() or LoadPrivateKey()
   - Use SignMessage() to sign any string
   - Use VerifySignature() for testing

3. **Key UE5 Adaptations:**
   - Uses UE5's TArray instead of std::vector
   - Uses FString instead of std::string
   - Implements UFUNCTION macros for Blueprint integration
   - Uses UE5's logging system (UE_LOG)
   - Follows UE5 naming conventions
   - Includes proper Blueprint integration
   - Uses UE5's UTF8 string conversion
   - Implements UCLASS for object management

4. **Testing:**
   - Call TestSigning() from Blueprint or C++
   - Check the Output Log for results
   - Integrate into your game's authentication system
*/
